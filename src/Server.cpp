#include <stdio.h>

#include "Server.hpp"
#include "Position.h"

#include <sstream>

#define HOST_NAME "localhost"

#define CONNECTION_TIMEOUT 5000
#define NUMBER_CHANNELS 2
#define NB_CLIENTS_MAX 4
#define DEFAULT_PORT 1234

const int PLAYER_WIDTH = 100;
const Position PLAYER1_SPAWN_POSITION = {100, 200};
const Position PLAYER2_SPAWN_POSITION = {700 - PLAYER_WIDTH / 2, 200};
const Position PLAYER3_SPAWN_POSITION = {400 - PLAYER_WIDTH / 2, 50};

Server *Server::m_instance = nullptr;

Server::Server() : m_host(nullptr), m_gamestate(new lambda::GameState()), m_player_id_counter(0)
{
}

Server::~Server()
{
    delete m_address;
}

void printPacketDescription(const lambda::GameState *gamestate)
{
    printf("\tPacket description:\n");
    printf("\tNb players: %d\n", gamestate->nb_players());
    for (int i = 0; i < gamestate->nb_players(); i++)
    {
        printf("\tPlayer %d: (%d,%d)\n", i + 1, gamestate->players_data(i).x(), gamestate->players_data(i).y());
    }
}

int Server::createServer()
{
    m_address = new ENetAddress();

    /* Bind the server to the default localhost.     */
    /* A specific host address can be specified by   */
    /* enet_address_set_host (& address, "x.x.x.x"); */
    m_address->host = ENET_HOST_ANY;
    /* Bind the server to port 1234. */
    m_address->port = DEFAULT_PORT;

    /* Creates the server */
    m_host = enet_host_create(m_address /* the address to bind the server host to */,
                              NB_CLIENTS_MAX /* allow up to 4 clients and/or outgoing connections */,
                              NUMBER_CHANNELS /* allow up to 2 channels to be used, 0 and 1 */,
                              0 /* assume any amount of incoming bandwidth */,
                              0 /* assume any amount of outgoing bandwidth */);
    if (m_host == NULL)
    {
        fprintf(stderr, "An error occurred while trying to create an ENet server host.\n");
        return -1;
    }

    return 1;
}

void Server::handlePacketReceipt(ENetEvent *net_event)
{
    switch (net_event->type)
    {
    // Only the "peer" field of the event structure is valid for this event
    case ENET_EVENT_TYPE_CONNECT:
    {
        printf("A new client connected from %x:%u.\n",
               net_event->peer->address.host,
               net_event->peer->address.port);

        // Add new player
        std::string client_address = getStringFromENetPeerAddress(net_event->peer);
        m_players_index[client_address] = m_clients.size();
        m_clients.push_back(net_event->peer);

        updateGamestateFirstConnection();
        broadcastGamestate();
        break;
    }

    case ENET_EVENT_TYPE_RECEIVE:
    {
        printf("\nA packet of length %lu was received from %d on channel %u.\n",
               net_event->packet->dataLength,
               net_event->peer->address.host,
               net_event->channelID);

        lambda::PlayerAction received_playerAction = getPlayerActionFromPacket(net_event->packet);

        std::string client_address = getStringFromENetPeerAddress(net_event->peer);

        // Update the player's position
        int player_index = m_players_index[client_address];
        m_gamestate->mutable_players_data(player_index)->set_x(received_playerAction.new_x());
        m_gamestate->mutable_players_data(player_index)->set_y(received_playerAction.new_y());

        broadcastGamestate();

        // Clean up the packet now that we're done using it.
        enet_packet_destroy(net_event->packet);

        break;
    }

    // Only the "peer" field of the event structure is valid for this event and contains the peer that disconnected
    case ENET_EVENT_TYPE_DISCONNECT:
        printf("%x:%hu disconnected.\n", net_event->peer->address.host, net_event->peer->address.port);

        disconnectPlayer(net_event->peer);

        // Notice connected clients that a client disconnected
        std::string disconnected_peer_address = getStringFromENetPeerAddress(net_event->peer);
        int disconnected_player_index = m_players_index[disconnected_peer_address];
        m_gamestate->set_player_disconnected_id(disconnected_player_index);

        broadcastGamestate();

        m_gamestate->clear_player_disconnected_id();
    }
}

void Server::updateGamestateFirstConnection()
{
    auto player_data = m_gamestate->add_players_data();
    m_gamestate->set_nb_players(m_clients.size());
    player_data->set_id(m_player_id_counter);

    if (m_gamestate->nb_players() == 1)
    {
        player_data->set_x(PLAYER1_SPAWN_POSITION.x);
        player_data->set_y(PLAYER1_SPAWN_POSITION.y);
    }
    else if (m_gamestate->nb_players() == 2)
    {
        player_data->set_x(PLAYER2_SPAWN_POSITION.x);
        player_data->set_y(PLAYER2_SPAWN_POSITION.y);
    }
    else if (m_gamestate->nb_players() == 3)
    {
        player_data->set_x(PLAYER3_SPAWN_POSITION.x);
        player_data->set_y(PLAYER3_SPAWN_POSITION.y);
    }
    else
    {
        player_data->set_x(0);
        player_data->set_y(0);
    }

    m_player_id_counter++;
    //event.peer->data = "Client dummy";
}

void Server::disconnect()
{
    //TODO: notice clients that the server disconnected

    enet_host_destroy(m_host);
}

void Server::disconnectPlayer(ENetPeer *peer)
{
    std::string peer_address = getStringFromENetPeerAddress(peer);
    int disconnected_player_index = m_players_index[peer_address];

    m_players_index.erase(peer_address);
    // Update the players' indexes
    for (auto const &[address, index] : m_players_index)
    {
        if (index > disconnected_player_index)
        {
            m_players_index[address] -= 1;
        }
    }

    m_gamestate->set_nb_players(m_gamestate->nb_players() - 1);
    m_clients.erase(m_clients.begin() + disconnected_player_index);
    m_gamestate->mutable_players_data()->erase(m_gamestate->players_data().begin() + disconnected_player_index);
}

void Server::broadcastGamestate() const
{
    std::string packet_data = getStringFromGamestate(m_gamestate);
    ENetPacket *packet = enet_packet_create(packet_data.data(), packet_data.size(), ENET_PACKET_FLAG_RELIABLE);

    // Send the number of players and the new positions to the connected players
    enet_host_broadcast(m_host, 0, packet);
    printf("Sending following packet to all clients :\n");
    printPacketDescription(m_gamestate);
}

const std::string Server::getStringFromGamestate(lambda::GameState *gamestate) const
{
    std::string serialized_gamestate;
    gamestate->SerializeToString(&serialized_gamestate);
    return serialized_gamestate;
}

const lambda::PlayerAction Server::getPlayerActionFromPacket(ENetPacket *packet) const
{
    lambda::PlayerAction received_playerAction;
    received_playerAction.ParseFromArray(packet->data, packet->dataLength);
    return received_playerAction;
}

const std::string Server::getStringFromENetPeerAddress(ENetPeer *peer) const
{
    return std::to_string(peer->address.host) + ":" + std::to_string(peer->address.port);
}

Server *Server::getInstance()
{
    if (Server::m_instance == NULL)
    {
        Server::m_instance = new Server();
        int response = m_instance->createServer();
        if (response < 0)
        {
            return NULL;
        }
    }
    return Server::m_instance;
}

ENetHost *Server::getHost() const
{
    return m_host;
}
