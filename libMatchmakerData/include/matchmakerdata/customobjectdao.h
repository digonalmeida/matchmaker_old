#ifndef CUSTOMOBJECTDAO_H
#define CUSTOMOBJECTDAO_H
#include <string>
#include "customobject.h"

using namespace std;

namespace mm
{

class DbConnection;

class CustomObjectDao
{

public:
    virtual bool loadCustomPropertiesWithFilter(const std::string& table, const std::string& filter, CustomObject& output) = 0;
    virtual bool remove(const std::string& table, const std::string& filter) = 0;
    virtual std::vector<int> queryIds(const std::string& table, const std::string& filter, int max, bool* ok = 0) = 0;

    std::vector<CustomObject> queryCustomObject(const std::string& table, const std::string& filter, int max, bool* ok = 0);

    bool saveCustomProperties(const std::string& table, CustomObject& object);

    bool loadCustomPropertiesWithId(const std::string& table, int id, CustomObject& output);
    bool loadCustomProperties(const std::string& table, CustomObject& output);
    bool remove(const std::string& table, CustomObject& object);
    bool remove(const std::string& table, int id);

    std::string getError() const
    {
        return m_error;
    }

protected:
    virtual bool insertObject(const std::string& table, CustomObject& object) = 0;
    virtual bool updateObject(const std::string& table, CustomObject& object) = 0;
    std::string m_error;
    DbConnection* m_dbConnection;
};

};

#endif
