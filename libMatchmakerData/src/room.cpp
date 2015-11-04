#include "room.h"
#include <string>

namespace mm
{

std::string Room::nullAddress = "";

Room::Room()
{
    m_available = false;
    m_matchId = CustomObject::nullId;
}

std::string Room::serverAddress() const
{
    return m_serverAddress;
}

bool Room::available() const
{
    return m_available;
}

void Room::setServerAddress(const std::string& serverAddress)
{
    m_serverAddress = serverAddress;
}

void Room::setAvailable(bool available)
{
    m_available = available;
}

int Room::matchId() const
{
    return m_matchId;
}

void Room::setMatchId(int id)
{
    m_matchId = id;
}
};
