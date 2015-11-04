#ifndef ROOMDAO_H
#define ROOMDAO_H

#include "room.h"
#include "customobjectdao.h"

namespace mm
{

class RoomDao : public virtual CustomObjectDao
{
public:
    RoomDao();
    virtual ~RoomDao();
    virtual bool saveRoom(Room& room) = 0;
    virtual bool loadRoom(Room& room) = 0;
    virtual bool removeRoom(Room& room) = 0;
protected:
private:
};

};
#endif // ROOMDAO_H
