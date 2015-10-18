#ifndef CUSTOMOBJECTDAOSOCI_H
#define CUSTOMOBJECTDAOSOCI_H

#include "customobjectdao.h"

namespace mm{

class SociDbConnection;

class CustomObjectDaoSoci : public CustomObjectDao
{
    public:
        CustomObjectDaoSoci(SociDbConnection* sociDbConnection);

        bool load(std::string table, std::string filter, CustomObject* output = 0);
        bool save(const CustomObject& object, const std::string& table);

    protected:
        SociDbConnection* m_sociDbConnection;

    private:
};

}

#endif // CUSTOMOBJECTDAOSOCI_H
