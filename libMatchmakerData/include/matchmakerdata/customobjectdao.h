#ifndef CUSTOMOBJECTDAO_H
#define CUSTOMOBJECTDAO_H
#include <string>
#include "customobject.h"

using namespace std;

namespace mm{

class DbConnection;

class CustomObjectDao{

public:
    virtual bool load(std::string table, std::string filter, CustomObject* output = 0) = 0;
    virtual bool save(const CustomObject& object, const std::string& table) = 0;

    std::string getError() { return m_error; }

protected:
    std::string m_error;
    DbConnection* m_dbConnection;
};

};

#endif
