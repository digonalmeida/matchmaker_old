#include "dbconnectionfactory.h"
#include "socidbconnection.h"

namespace mm
{


DbConnectionFactory::DbConnectionFactory()
{
    //ctor
}

std::shared_ptr<DbConnection> DbConnectionFactory::makeConnection(ConnectionType type, std::string host, std::string user, std::string pass, std::string database)
{

    if(type == DbConnectionFactory::CONNECTION_TYPE_SOCI_POSTGRESQL){
        std::shared_ptr<SociDbConnection> dbConnection(new SociDbConnection());
        SociDbConnection* sociCon = (SociDbConnection*) &(*dbConnection);
        sociCon->connect(SociDbConnection::POSTGRESQL, host, user, pass, database);
        return dbConnection;
    }
    return std::shared_ptr<DbConnection>(0);
}

}
