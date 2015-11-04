#include "request.h"
#include "profile.h"
namespace mm
{

Request::Request()
{
    m_profileId = Profile::nullId;
    m_state = ' ';

    time_t currentTime = time(0);
    m_dateTime = *localtime(&currentTime);
}

int Request::profileId()
{
    return m_profileId;
}

void Request::setProfileId(int id)
{
    m_profileId = id;
}

std::string Request::state()
{
    return m_state;
}

void Request::setState(std::string s)
{
    m_state = s;
}

std::tm Request::dateTime() const
{
    return m_dateTime;
}

void Request::setDateTime(const std::tm& dateTime)
{
    m_dateTime = dateTime;
}

void Request::setRoomId(int roomId)
{
    m_roomId = roomId;
}
};
