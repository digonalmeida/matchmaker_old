#ifndef CUSTOMOBJECTDAO_H
#define CUSTOMOBJECTDAO_H

#include <string>

#include "customobject.h"
#include "dbconnection.h"

using namespace std;

namespace mm{

class CustomObjectDao{

public:
    bool load(string table, string filter, CustomObject& output);
    bool save(const CustomObject& object);

    string getError();

protected:
    string error;
};

};

#endif
