#include "dbconnectionfactory.h"
#include "socidbconnection.h"

using namespace mm;
DbConnectionFactory::DbConnectionFactory()
{
    //ctor
}

std::shared_ptr<DbConnection> DbConnectionFactory::makeConnection(std::string type, std::string host, std::string user, std::string pass, std::string database)
{

    if(type == "postgresql"){
        std::shared_ptr<SociDbConnection> dbConnection(new SociDbConnection());
        SociDbConnection* sociCon = (SociDbConnection*) &(*dbConnection);
        sociCon->connect("postgresql", host, user, pass, database);
        return dbConnection;
    }
    return std::shared_ptr<DbConnection>(0);
}
