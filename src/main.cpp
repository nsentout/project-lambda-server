#include <stdio.h>
#include <stdlib.h>

#include <chrono>

#include "../proto/movement.pb.h"
#include "Server.hpp"

#define TICKRATE 64
#define POLL_INTERVAL (1000 / 64) / 1000

using namespace std;

int main(int argc, char **argv)
{
    Server *server = Server::getInstance();
    int i = 0;

    if (server != NULL)
    {
        puts("Server listening ...");

        char *packetReceived;
        ENetEvent event;
        auto start = chrono::system_clock::now();

        while (true)
        {
            std::chrono::duration<double> elapsed_seconds = chrono::system_clock::now() - start;
            if (elapsed_seconds.count() > POLL_INTERVAL)
            {
                start = chrono::system_clock::now();

                server->checkPacketBox(packetReceived);

                // Empty the packet
                packetReceived = NULL;
                i++;
            }
        }

        delete packetReceived;
    }

    delete server;
}