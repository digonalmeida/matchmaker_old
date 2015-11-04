#include "socidbconnection.h"
#include "customobjectdaosoci.h"

#include <iostream>
namespace mm
{
SociDbConnection::SociDbConnection()
{
    //ctor
    m_driver = NONE;
    m_type = "SOCI";
    m_isConnected = false;

    CustomObjectDaoSoci* customObjectDao = new CustomObjectDaoSoci(this);
    m_customObjectDao = std::shared_ptr<CustomObjectDaoSoci>(customObjectDao);

    MatchDaoSoci* matchDao = new MatchDaoSoci(this);
    m_matchDao = std::shared_ptr<MatchDaoSoci>(matchDao);

    ProfileDaoSoci* profileDao = new ProfileDaoSoci(this);
    m_profileDao = std::shared_ptr<ProfileDaoSoci>(profileDao);

    RequestDaoSoci* requestDao = new RequestDaoSoci(this);
    m_requestDao = std::shared_ptr<RequestDaoSoci>(requestDao);

    RoomDaoSoci* roomDao = new RoomDaoSoci(this);
    m_roomDao = std::shared_ptr<RoomDaoSoci>(roomDao);

}

SociDbConnection::~SociDbConnection()
{
    //dtor
}
bool SociDbConnection::connect(DatabaseDriver connectionDriver, std::string host, std::string user, std::string pass, std::string database)
{
    m_isConnected = false;
    m_session = std::shared_ptr<soci::session>(new soci::session());
    if(connectionDriver == POSTGRESQL)
    {
        m_driver = POSTGRESQL;
        std::string connectionString = "host='" + host + "' user='" + user + "' password='" + pass + "' dbname='" + database + "'";
        m_session->open(soci::postgresql, connectionString);
        m_isConnected = true;
        return true;
    }
    else
    {
        return false;
    }
}

std::shared_ptr<soci::session> SociDbConnection::session()
{
    return m_session;
}
std::shared_ptr<CustomObjectDao> SociDbConnection::customObjectDao()
{
    return static_pointer_cast<CustomObjectDao>(m_customObjectDao);
}
std::shared_ptr<MatchDao> SociDbConnection::matchDao()
{
    return static_pointer_cast<MatchDao>(m_matchDao);
}
std::shared_ptr<ProfileDao> SociDbConnection::profileDao()
{
    return static_pointer_cast<ProfileDao>(m_profileDao);
}
std::shared_ptr<RequestDao> SociDbConnection::requestDao()
{
    return static_pointer_cast<RequestDao>(m_requestDao);
}
std::shared_ptr<RoomDao> SociDbConnection::roomDao()
{
    return static_pointer_cast<RoomDao>(m_roomDao);
}

SociDbConnection::DatabaseDriver SociDbConnection::databaseDriver()
{
    return m_driver;
}

};
