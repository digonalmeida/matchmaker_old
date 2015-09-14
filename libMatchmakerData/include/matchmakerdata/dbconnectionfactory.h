#ifndef DBCONNECTIONFACTORY_H
#define DBCONNECTIONFACTORY_H

#include "dbconnection.h"
#include <string>
#include <memory>

namespace mm{
    class DBConnectionFactory;

class DBConnectionFactory
{
    public:
        DBConnectionFactory();
        std::shared_ptr<DBConnection> makeConnection(std::string type, std::string host, std::string user, std::string pass, std::string database);
    protected:
    private:
};

};

#endif // DBCONNECTIONFACTORY_H
