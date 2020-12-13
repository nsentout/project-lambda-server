#include <stdio.h>
#include <string.h>

#include "Server.hpp"

#include <iostream>
#include <sstream>

#define HOST_NAME "localhost"

#define CONNECTION_TIMEOUT 5000
#define NUMBER_CHANNELS 2
#define NB_CLIENTS_MAX 4
#define DEFAULT_PORT 1234

#define TICKRATE 64
#define POLL_INTERVAL 1000 / 64

Server *Server::m_instance = nullptr;

Server::Server() : m_host(nullptr)
{
}

Server::~Server()
{
    this->disconnect();

    
}

int Server::createServer()
{
    ENetAddress address;

    /* Bind the server to the default localhost.     */
    /* A specific host address can be specified by   */
    /* enet_address_set_host (& address, "x.x.x.x"); */
    address.host = ENET_HOST_ANY;
    /* Bind the server to port 1234. */
    address.port = DEFAULT_PORT;

    /* Creates the server */
    m_host = enet_host_create(&address /* the address to bind the server host to */,
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
 * If there is, packetReceived will be assigned its value.
 * 
 * @return a integer greater than 0, if a packet is in the waiting queue, -1 otherwise @return
 *
 */
void Server::checkPacketBox(char *packetReceived)
{
    ENetEvent event;
    if (enet_host_service(m_host, &event, 0) > 0)
    {
        switch (event.type)
        {
        // Only the "peer" field of the event structure is valid for this event
        case ENET_EVENT_TYPE_CONNECT:
        {
            printf("A new client connected from %x:%u.\n",
                   event.peer->address.host,
                   event.peer->address.port);
            
            m_clients.push_back(event.peer);
            //event.peer->data = "Client dummy";
            break;
        }

        // The "peer" field contains the peer the packet was received from, "channelID" is the channel on
        // which the packet was sent, and "packet" is the packet that was sent.
        case ENET_EVENT_TYPE_RECEIVE:
        {
            std::istringstream unserialized_movement(reinterpret_cast<char const *>(event.packet->data));
            lambda::Movement movement;
            movement.ParseFromIstream(&unserialized_movement);

            printf("A packet of length %u containing '%d' was received from %s on channel %u.\n",
                   event.packet->dataLength,
                   movement.direction(),
                   event.peer->data,
                   event.channelID);

            packetReceived = (char *)event.packet->userData;

            ENetPacket *packet = enet_packet_create(event.packet->data, strlen(event.packet->data) + 1, ENET_PACKET_FLAG_UNRELIABLE_FRAGMENT);
            enet_host_broadcast(m_host, 0, event.packet);
            puts("Sending packet to all clients.");

            /* Clean up the packet now that we're done using it. */
            enet_packet_destroy(event.packet);

            break;
        }

        // Only the "peer" field of the event structure is valid for this event and contains the peer that disconnected
        case ENET_EVENT_TYPE_DISCONNECT:
            printf("%s disconnected.\n", event.peer->data);
            /* Reset the peer's client information. */
            event.peer->data = NULL;
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