#ifndef DBCONNECTION_H
#define DBCONNECTION_H
#include <string>
#include <memory>
#include "customobjectdao.h"

namespace mm{

class CustomObjectDao;

class DbConnection
{
    public:
        DbConnection() {}
        virtual ~DbConnection() {}
        virtual bool isConnected() { return m_isConnected; }
        std::string type() const { return m_type; }
        std::shared_ptr<CustomObjectDao> customObjectDao();

    protected:
        bool m_isConnected;
        std::string m_type;
    private:

};

};

#endif // DBCONNECTION_H
