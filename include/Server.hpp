#ifndef SERVER_HPP
#define SERVER_HPP

#include <enet/enet.h>

#include "../../proto/gamestate.pb.h"

#include <vector>

class Server
{
private:
    ENetHost *m_host;
    ENetAddress *m_address;
    std::vector<ENetPeer*> m_clients;

    lambda::GameState *m_gamestate;
    
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
