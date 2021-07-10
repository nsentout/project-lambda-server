#ifndef SERVER_HPP
#define SERVER_HPP

#include <enet/enet.h>

#include "../../proto/gamestate.pb.h"
#include "../../proto/playeraction.pb.h"

#include <string>
#include <vector>
#include <map>

class Server
{
private:
    ENetHost *m_host;
    ENetAddress *m_address;
    std::vector<ENetPeer*> m_clients;

    /**
     * Link the client's address to its index in the positions array
     */
    std::map<std::string, int> m_players_index;

    lambda::GameState *m_gamestate;
    
    static Server *m_instance;
    int createServer();
    void updateGamestateFirstConnection(ENetPeer *new_client);
    void disconnectPlayer(ENetPeer *peer);
    void updateGamestateFirstConnection();
    void broadcastGamestate();
    const std::string  getStringFromGamestate(lambda::GameState *gamestate) const;
    const std::string getStringFromENetPeerAddress(ENetPeer *peer) const;
    const lambda::PlayerAction getPlayerActionFromPacket(ENetEvent *net_event) const;

public:
    Server();
    virtual ~Server();

    void sendPacket(const char* packetContent);
    void checkPacketBox(ENetEvent *net_event, char *packetReceived);
    void disconnect();

    static Server* getInstance();

    ENetHost* getHost();
};

#endif
