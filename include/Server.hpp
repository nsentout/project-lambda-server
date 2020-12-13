#ifndef SERVER_H
#define SERVER_H

#include <enet/enet.h>

#include "../proto/movement.pb.h"

#include <vector>

class Server
{
private:
    ENetHost *m_host;
    std::vector<ENetPeer*> m_clients;
    
    static Server *m_instance;
    int createServer();

public:
    Server();
    virtual ~Server();

    void sendPacket(const char* packetContent);
    void checkPacketBox(char *packetReceived);
    void disconnect();

    static Server* getInstance();

    ENetHost* getHost();
};

#endif
