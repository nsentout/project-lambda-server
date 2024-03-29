#ifndef SERVER_HPP
#define SERVER_HPP

#include <enet/enet.h>

#include "gamestate.pb.h"
#include "playeraction.pb.h"

#include <string>
#include <vector>
#include <map>

class Server
{
private:
    ENetHost *m_host;
    ENetAddress *m_address;

    /**
     *  All the peers connected to the server
     */
    std::vector<ENetPeer*> m_clients;

    /**
     * Link the client's address to its index in the players' position array
     */
    std::map<std::string, int> m_players_index;

    lambda::GameState *m_gamestate;

    int m_player_id_counter;
    
    static Server *m_instance;

    int createServer();
    void updateGamestateFirstConnection(ENetPeer *new_client);
    void disconnectPlayer(ENetPeer *peer);
    void updateGamestateFirstConnection();
    void broadcastGamestate() const;
    const std::string getStringFromGamestate(lambda::GameState *gamestate) const;
    const std::string getStringFromENetPeerAddress(ENetPeer *peer) const;
    const lambda::PlayerAction getPlayerActionFromPacket(ENetPacket *packet) const;

public:
    Server();
    virtual ~Server();

    void sendPacket(const char* packet_content);
    void handlePacketReceipt(ENetEvent *net_event);
    void disconnect();

    static Server* getInstance();

    ENetHost* getHost() const;
};

#endif
