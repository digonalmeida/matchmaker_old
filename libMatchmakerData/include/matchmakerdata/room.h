#ifndef ROOM_H
#define ROOM_H

#include <string>
#include "customobject.h"

namespace mm
{
class Room : public CustomObject
{
public:
    static std::string nullAddress;
    Room();
    std::string serverAddress() const ;
    bool available() const;
    int matchId() const;

    void setServerAddress(const std::string &serverAddress);
    void setAvailable(bool available);
    void setMatchId(int m);
private:
    std::string m_serverAddress;
    bool m_available;
    int m_matchId;
};
};

#endif
