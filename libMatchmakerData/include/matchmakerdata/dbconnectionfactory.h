#ifndef DBCONNECTIONFACTORY_H
#define DBCONNECTIONFACTORY_H

#include <string>
#include <memory>

namespace mm{
    class DbConnection;

class DbConnectionFactory
{
    public:
        DbConnectionFactory();
        std::shared_ptr<DbConnection> makeConnection(std::string type, std::string host, std::string user, std::string pass, std::string database);
    protected:
    private:
};

};

#endif // DBCONNECTIONFACTORY_H
