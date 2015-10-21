#include "room.h"
#include <string>

namespace mm
{
int Room::nullId = -1;
std::string Room::nullAddress = "";

Room::Room(){
    m_id = Room::nullId;
    m_available = false;
}

int Room::id() const
{
    return m_id;
}

std::string Room::serverAddress() const
{
    return m_serverAddress;
}

bool Room::available() const
{
    return m_available;
}

void Room::setId(int id){
    m_id = id;
}

void Room::setServerAddress(const std::string& serverAddress)
{
    m_serverAddress = serverAddress;
}

void Room::setAvailable(bool available)
{
    m_available = available;
}
};
