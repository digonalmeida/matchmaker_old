#ifndef SOCIDBCONNECTION_H
#define SOCIDBCONNECTION_H

#include <memory>
#include <soci/session.h>
#include <soci/postgresql/soci-postgresql.h>
#include <soci/session.h>

#include "dbconnection.h"
#include "customobjectdaosoci.h"

namespace mm{

class SociDbConnection : public DbConnection {
    public:
        SociDbConnection();

        enum DatabaseDriver{
            POSTGRESQL
        };

        bool connect(DatabaseDriver driver, std::string host, std::string user, std::string pass, std::string database);
        ~SociDbConnection();

        std::shared_ptr<soci::session> session() { return m_session; }
        std::shared_ptr<CustomObjectDao> customObjectDao() { return static_pointer_cast<CustomObjectDao>(m_customObjectDao); }

    protected:
        std::shared_ptr<CustomObjectDaoSoci> m_customObjectDao;

    private:
        std::shared_ptr<soci::session> m_session;
};

};

#endif // SOCIDBCONNECTION_H
