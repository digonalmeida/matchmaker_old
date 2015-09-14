#include "dbconnectionfactory.h"
#include "socidbconnection.h"

using namespace mm;
DBConnectionFactory::DBConnectionFactory()
{
    //ctor
}

std::shared_ptr<DBConnection> DBConnectionFactory::makeConnection(std::string type, std::string host, std::string user, std::string pass, std::string database)
{

    if(type == "postgres"){
        std::shared_ptr<DBConnection> dbConnection(new SOCIDBConnection());
        SOCIDBConnection* sociCon = (SOCIDBConnection*) &(*dbConnection);
        sociCon->connect("postgres", host, user, pass, database);
        return dbConnection;
    }
    return std::shared_ptr<DBConnection>(0);
}
