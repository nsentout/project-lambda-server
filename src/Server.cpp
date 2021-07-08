#include <stdio.h>
#include <string.h>

#include "Server.hpp"
#include "Position.hpp"

#include <iostream>
#include <sstream>

#define HOST_NAME "localhost"

#define CONNECTION_TIMEOUT 5000
#define NUMBER_CHANNELS 2
#define NB_CLIENTS_MAX 4
#define DEFAULT_PORT 1234

const int PLAYER_WIDTH = 100;
const Position PLAYER1_SPAWN_POSITION = { 100, 200 };
const Position PLAYER2_SPAWN_POSITION = { 700 - PLAYER_WIDTH / 2, 200 };
const Position PLAYER3_SPAWN_POSITION = { 400 - PLAYER_WIDTH / 2, 50 };

Server *Server::m_instance = nullptr;

Server::Server() : m_host(nullptr), m_gamestate(new lambda::GameState())
{
 
}

Server::~Server()
{
    this->disconnect();
    delete m_address;
}

void printPacketDescription(const lambda::GameState *gamestate)
{
    printf("Packet description:\n");
    printf("Nb players: %d\n", gamestate->nb_players());
    for (int i = 0; i < gamestate->nb_players(); i++) {
        printf("Player %d: (%d,%d)\n", i+1, gamestate->players_data(i).x(), gamestate->players_data(i).y());
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

/**
 * Checks if a packet is in the waiting queue.
 * If there is, packet_received will be assigned its value.
 */
void Server::checkPacketBox(char *packet_received)
{
    ENetEvent net_event;
    while (enet_host_service(m_host, &net_event, 0) > 0)
    {
        switch (net_event.type)
        {
        // Only the "peer" field of the event structure is valid for this event
        case ENET_EVENT_TYPE_CONNECT:
        {
            printf("A new client connected from %x:%u.\n",
                   net_event.peer->address.host,
                   net_event.peer->address.port);
            
            m_clients.push_back(net_event.peer);

            auto player_data = m_gamestate->add_players_data();
            m_gamestate->set_nb_players(m_clients.size());

            if (m_gamestate->nb_players() == 1) {
                player_data->set_x(PLAYER1_SPAWN_POSITION.getX());
                player_data->set_y(PLAYER1_SPAWN_POSITION.getY());
            }
            else if (m_gamestate->nb_players() == 2) {
                player_data->set_x(PLAYER2_SPAWN_POSITION.getX());
                player_data->set_y(PLAYER2_SPAWN_POSITION.getY());
            }
            else if (m_gamestate->nb_players() == 3) {
                player_data->set_x(PLAYER3_SPAWN_POSITION.getX());
                player_data->set_y(PLAYER3_SPAWN_POSITION.getY());
            }
            else {
                player_data->set_x(0);
                player_data->set_y(0);
            }

            std::ostringstream serialized_gamestate;
            m_gamestate->SerializeToOstream(&serialized_gamestate);

            const char* packet_data = serialized_gamestate.str().c_str();
            ENetPacket *packet = enet_packet_create(packet_data, strlen(packet_data), ENET_PACKET_FLAG_RELIABLE);

            // Send the number of players and the new positions to the connected players
            enet_host_broadcast(m_host, 0, packet);
            printf("Sending packet to all clients.\n");
            printPacketDescription(m_gamestate);

            //event.peer->data = "Client dummy";
            break;
        }

        case ENET_EVENT_TYPE_RECEIVE:
        {
            std::istringstream unserialized_gamestate(reinterpret_cast<char const *>(net_event.packet->data));
            lambda::GameState received_gamestate;
            received_gamestate.ParseFromIstream(&unserialized_gamestate);

            printf("A packet of length %u was received from %d on channel %u.\n",
                   net_event.packet->dataLength,
                   net_event.peer->address.host,
                   net_event.channelID);
            ENetPeer *peer = net_event.peer;
            packet_received = (char *)net_event.packet->data;
            //TODO: mettre à jour le gamestate avec les infos recus
            //TODO: client se déco tout seul ?

            puts("===\nserver send\n===");
            printPacketDescription(&received_gamestate);

            const char* packet_received_data = unserialized_gamestate.str().c_str();
            //ENetPacket *packet = enet_packet_create(net_event.packet->data, strlen(net_event.packet->data), ENET_PACKET_FLAG_UNRELIABLE_FRAGMENT);
            //enet_host_broadcast(m_host, 0, net_event.packet);
            ENetPacket *packet = enet_packet_create(packet_received_data, strlen(packet_received_data), ENET_PACKET_FLAG_UNRELIABLE_FRAGMENT);
            enet_host_broadcast(m_host, 0, packet);
            puts("Sending packet direction to all clients.");

            /* Clean up the packet now that we're done using it. */
            enet_packet_destroy(net_event.packet);

            break;
        }

        // Only the "peer" field of the event structure is valid for this event and contains the peer that disconnected
        case ENET_EVENT_TYPE_DISCONNECT:
            printf("%x disconnected.\n", net_event.peer->address.host);

            m_gamestate->set_nb_players(m_gamestate->nb_players() - 1) ;
        }
    }
}

void Server::disconnect()
{
    //TODO: notice clients

    enet_host_destroy(m_host);
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

ENetHost* Server::getHost() 
{
    return m_host;    
}
