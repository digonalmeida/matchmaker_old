#ifndef DBCONNECTIONFACTORY_H
#define DBCONNECTIONFACTORY_H

#include <string>
#include <memory>

namespace mm
{

class DbConnection;

class DbConnectionFactory
{
public:
    DbConnectionFactory();

    enum ConnectionType
    {
        CONNECTION_TYPE_SOCI_POSTGRESQL
    };
    std::shared_ptr<DbConnection> makeConnection(const std::string iniFileName);
    std::shared_ptr<DbConnection> makeConnection(ConnectionType type, std::string host, std::string user, std::string pass, std::string database);
protected:
private:
};

};

#endif // DBCONNECTIONFACTORY_H
