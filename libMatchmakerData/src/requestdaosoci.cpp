#include "requestdaosoci.h"

namespace mm
{

RequestDaoSoci::RequestDaoSoci(mm::SociDbConnection* connection)
    : CustomObjectDaoSoci(connection)
{
    m_table = "request";
    //ctor
}

RequestDaoSoci::~RequestDaoSoci()
{
    //dtor
}

bool RequestDaoSoci::saveRequest(Request& request){
    if(request.profileId() == CustomObject::nullId){
        request.setNull("id_profile");
    }
    else
    {
        request.addField("id_profile");
        request.set<int>("id_profile", request.profileId());
    }
    if(request.roomId() == CustomObject::nullId){
        request.setNull("id_room");
    }
    else
    {
        request.addField("id_room");
        request.set<int>("id_room", request.roomId());
    }

    request.addField("date_time");
    request.set<std::tm>("date_time", request.dateTime());
    request.addField("state");
    request.set<std::string>("state", request.state());

    bool saved = saveCustomProperties(m_table, request);
    return saved;
}

bool RequestDaoSoci::loadRequest(Request& request){
    bool loaded = loadCustomProperties(m_table, request);
    if(!request.isNull("id_profile"))
    {
        request.setProfileId(request.get<int>("id_profile"));
    }
    if(!request.isNull("date_time"))
    {
        request.setDateTime(request.get<std::tm>("date_time"));
    }
    if(!request.isNull("state"))
    {
        request.setState(request.get<std::string>("state"));
    }
    if(!request.isNull("id_room"))
    {
        request.setRoomId(request.get<int>("id_room"));
    }
    return loaded;
}

bool RequestDaoSoci::removeRequest(Request& request)
{
    bool removed = RequestDao::remove(m_table, request);
    return removed;
}
};

