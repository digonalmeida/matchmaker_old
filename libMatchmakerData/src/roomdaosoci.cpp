#include "roomdaosoci.h"

namespace mm
{

RoomDaoSoci::RoomDaoSoci(mm::SociDbConnection* connection)
    : CustomObjectDaoSoci(connection)
{
    //ctor
    m_table = "room";
}

RoomDaoSoci::~RoomDaoSoci()
{
    //dtor
}

bool RoomDaoSoci::saveRoom(Room& room)
{
    if(room.matchId() == CustomObject::nullId)
    {
        room.setNull("id_match");
    }
    else
    {
        room.addField("id_match");
        room.set<int>("id_match", room.matchId());
    }

    room.addField("server_address");
    room.set<std::string>("server_address", room.serverAddress());

    room.addField("available");
    room.set<std::string>("available", room.available() ? "Y" : "N");

    bool saved = saveCustomProperties(m_table, room);

    return saved;
}

bool RoomDaoSoci::loadRoom(Room& room)
{
    bool loaded = loadCustomProperties(m_table, room);
    if(!room.isNull("id_match"))
    {
        room.setMatchId(room.get<int>("id_match"));
    }

    if(!room.isNull("server_address"))
    {
        room.setServerAddress(room.get<std::string>("server_address"));
    }

    if(!room.isNull("available"))
    {
        room.setAvailable(room.get<std::string>("available") == "Y" ? true : false);
    }

    return loaded;
}

bool RoomDaoSoci::removeRoom(Room& room)
{
    bool removed = RoomDao::remove(m_table, room);
    return removed;
}

};
