#ifndef SOCIDBCONNECTION_H
#define SOCIDBCONNECTION_H

#include <memory>
#include <soci/session.h>
#include <soci/postgresql/soci-postgresql.h>
#include <soci/session.h>

#include "dbconnection.h"
#include "customobjectdaosoci.h"
#include "matchdaosoci.h"
#include "profiledaosoci.h"
#include "requestdaosoci.h"
#include "roomdaosoci.h"

namespace mm
{

class SociDbConnection : public DbConnection
{
public:
    SociDbConnection();

    enum DatabaseDriver
    {
        NONE,
        POSTGRESQL
    };

    bool connect(DatabaseDriver driver, std::string host, std::string user, std::string pass, std::string database);
    ~SociDbConnection();

    std::shared_ptr<soci::session> session();
    std::shared_ptr<CustomObjectDao> customObjectDao();
    std::shared_ptr<MatchDao> matchDao();
    std::shared_ptr<ProfileDao> profileDao();
    std::shared_ptr<RequestDao> requestDao();
    std::shared_ptr<RoomDao> roomDao();

    DatabaseDriver databaseDriver();

protected:
    std::shared_ptr<CustomObjectDaoSoci> m_customObjectDao;
    std::shared_ptr<MatchDaoSoci> m_matchDao;
    std::shared_ptr<ProfileDaoSoci> m_profileDao;
    std::shared_ptr<RequestDaoSoci> m_requestDao;
    std::shared_ptr<RoomDaoSoci> m_roomDao;

private:
    std::shared_ptr<soci::session> m_session;
    DatabaseDriver m_driver;
};

};

#endif // SOCIDBCONNECTION_H
