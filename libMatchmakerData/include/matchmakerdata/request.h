#ifndef REQUEST_H
#define REQUEST_H

#include "customobject.h"
#include "profile.h"

namespace mm
{

class Request: public CustomObject
{
public:
    Request();

    static int nullId;
    int id();
    int profileId();

    void setId(int id);
    void setProfileId(int id);

private:
    int m_id;
    int m_profileId;
};


};

#endif
