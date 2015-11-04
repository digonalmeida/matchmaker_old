#ifndef DBCONNECTION_H
#define DBCONNECTION_H
#include <string>
#include <memory>
#include "customobjectdao.h"
#include "matchdao.h"
#include "profiledao.h"
#include "requestdao.h"
#include "roomdao.h"


namespace mm
{

class DbConnection
{
public:
    DbConnection() {}
    virtual ~DbConnection() {}
    virtual bool isConnected()
    {
        return m_isConnected;
    }
    std::string type() const
    {
        return m_type;
    }

    virtual shared_ptr<CustomObjectDao> customObjectDao() = 0;
    virtual shared_ptr<MatchDao> matchDao() = 0;
    virtual shared_ptr<ProfileDao> profileDao() = 0;
    virtual shared_ptr<RoomDao> roomDao() = 0;
    virtual shared_ptr<RequestDao> requestDao() = 0;

protected:
    bool m_isConnected;
    std::string m_type;
private:

};

};

#endif // DBCONNECTION_H
