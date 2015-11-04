#ifndef CUSTOMOBJECTDAOSOCI_H
#define CUSTOMOBJECTDAOSOCI_H
#include <soci.h>

#include "customobjectdao.h"

namespace mm
{

class SociDbConnection;

class CustomObjectDaoSoci : public virtual CustomObjectDao
{
public:
    CustomObjectDaoSoci(SociDbConnection* sociDbConnection);

    bool loadCustomPropertiesWithFilter(const std::string& table, const std::string& filter, CustomObject& output) override;
    std::vector<int> queryIds(const std::string& table, const std::string& filter, int max, bool* ok = 0) override;
    bool remove(const std::string& table, const std::string& filter);

protected:
    SociDbConnection* m_sociDbConnection;
    bool updateObject(const std::string& table, CustomObject& object);
    bool insertObject(const std::string& table, CustomObject& object);

private:
    struct StatementMapping{
        std::map<std::string, int> intValues;
        std::map<std::string, std::string> strValues;
        std::map<std::string, double> doubleValues;
        std::map<std::string, std::tm> tmValues;
        std::map<std::string, long> longValues;
        std::map<std::string, long long> llongValues;
        std::map<std::string, unsigned long long> ullongValues;
    };
    void statementExchange(soci::statement& statement,
                            CustomObject& object,
                            const std::string& field,
                            StatementMapping& mapping);
};

}

#endif // CUSTOMOBJECTDAOSOCI_H
