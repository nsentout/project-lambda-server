#include <stdio.h>
#include <stdlib.h>

#include "gamestate.pb.h"
#include "Server.hpp"

#define TICKRATE 64
#define POLL_INTERVAL_MS (1000.0 / TICKRATE)

using namespace std;

int main(int argc, char **argv)
{
    if (enet_initialize () != 0)
    {
        fprintf (stderr, "An error occurred while initializing ENet.\n");
        return EXIT_FAILURE;
    }

    Server *server = Server::getInstance();

    if (server != NULL)
    {
        puts("Server is listening ...");
        printf("Poll interval: %f ms\n", POLL_INTERVAL_MS);

        ENetEvent net_event;

        while (true)
        {
            while (enet_host_service(server->getHost(), &net_event, POLL_INTERVAL_MS) > 0)
            {
                server->handlePacketReceipt(&net_event);
            }
        }

    }

    server->disconnect();
    delete server;

    enet_deinitialize();
}