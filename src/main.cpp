#include <stdio.h>
#include <stdlib.h>

#include <chrono>

#include "../../proto/gamestate.pb.h"
#include "Server.hpp"

#define TICKRATE 64
#define POLL_INTERVAL (1000.0 / TICKRATE) / 1000.0

using namespace std;

int main(int argc, char **argv)
{
    if (enet_initialize () != 0)
    {
        fprintf (stderr, "An error occurred while initializing ENet.\n");
        return EXIT_FAILURE;
    }

    Server *server = Server::getInstance();
    int i = 0;

    if (server != NULL)
    {
        puts("Server is listening ...");
        printf("Poll interval: %f\n", POLL_INTERVAL);

        char *packet_received;
        ENetEvent net_event;
        auto start = chrono::system_clock::now();

        while (true)
        {
            std::chrono::duration<double> elapsed_seconds = chrono::system_clock::now() - start;
            if (elapsed_seconds.count() > POLL_INTERVAL)
            {
                start = chrono::system_clock::now();

                server->checkPacketBox(packet_received);

                // Empty the packet
                packet_received = NULL;
                i++;
            }
        }

        delete packet_received;
    }

    delete server;
    enet_deinitialize();
}