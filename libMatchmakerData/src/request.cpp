#include "request.h"
#include "profile.h"
namespace mm
{
int Request::nullId = -1;

Request::Request()
{
    m_id = Request::nullId;
    m_profileId = Profile::nullId;
}

int Request::id()
{
    return m_id;
}

void Request::setId(int id)
{
    m_id = id;
}

int Request::profileId(){
    return m_profileId;
}

void Request::setProfileId(int id){
    m_profileId = id;
}

};
