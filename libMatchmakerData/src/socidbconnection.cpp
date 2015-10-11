#include "socidbconnection.h"
#include "customobjectdaosoci.h"

#include <iostream>
namespace mm{
SociDbConnection::SociDbConnection()
{
    //ctor
    m_type = "SOCI";
    m_isConnected = false;

    CustomObjectDaoSoci* customObject = new CustomObjectDaoSoci(this);
    m_customObjectDao = std::shared_ptr<CustomObjectDaoSoci>(customObject);
}

SociDbConnection::~SociDbConnection()
{
    //dtor
}
bool SociDbConnection::connect(DatabaseDriver connectionDriver, std::string host, std::string user, std::string pass, std::string database)
{
    m_isConnected = false;
    m_session = std::shared_ptr<soci::session>(new soci::session());
    if(connectionDriver == POSTGRESQL){
        std::string connectionString = "host='" + host + "' user='" + user + "' password='" + pass + "' dbname='" + database + "'";
        m_session->open(soci::postgresql, connectionString);
        m_isConnected = true;
        return true;
    }
    else{
        return false;
    }
}

std::shared_ptr<CustomObjectDao> SociDbConnection::customObjectDao(){
    return m_customObjectDao;
}

};
