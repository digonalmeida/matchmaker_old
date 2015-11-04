#ifndef ROOMDAOSOCI_H
#define ROOMDAOSOCI_H

#include "roomdao.h"
#include "customobjectdaosoci.h"

namespace mm
{

class RoomDaoSoci: public RoomDao, public CustomObjectDaoSoci
{
    public:
        RoomDaoSoci(mm::SociDbConnection* connection);
        virtual ~RoomDaoSoci();
        bool saveRoom(Room& room) override;
        bool loadRoom(Room& room) override;
        bool removeRoom(Room& room) override;

    protected:
    private:
        std::string m_table;
};

};
#endif // ROOMDAOSOCI_H
