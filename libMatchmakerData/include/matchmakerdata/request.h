#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <ctime>

#include "customobject.h"
#include "profile.h"

namespace mm
{

class Request: public CustomObject
{
public:
    Request();
    int profileId();
    std::string state();
    int roomId();
    std::tm dateTime() const;

    void setProfileId(int id);
    void setState(std::string s);
    void setDateTime(const std::tm& dateTime);

private:
    int m_profileId;
    int m_matchId;
    int m_roomId;

    std::string m_state;
    std::tm m_dateTime;
};


};

#endif
