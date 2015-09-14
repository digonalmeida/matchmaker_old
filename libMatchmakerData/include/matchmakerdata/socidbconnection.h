#ifndef SOCIDBCONNECTION_H
#define SOCIDBCONNECTION_H

#include <memory>
#include "dbconnection.h"
#include <soci/session.h>

#include <soci/session.h>
#include <soci/postgresql/soci-postgresql.h>
#include <soci/session.h>

using namespace mm;

class SOCIDBConnection : public DBConnection
{
    public:
        SOCIDBConnection();
        bool connect(std::string type, std::string host, std::string user, std::string pass, std::string database);
        ~SOCIDBConnection();
        std::shared_ptr<soci::session> session() { return m_session; }
    protected:
    private:
        std::shared_ptr<soci::session> m_session;
};

#endif // SOCIDBCONNECTION_H
