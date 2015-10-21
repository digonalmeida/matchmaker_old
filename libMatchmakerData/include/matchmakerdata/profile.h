#include <string>
#include "customobject.h"
#ifndef PROFILE_H
#define PROFILE_H

namespace mm
{

class Profile : public CustomObject
{
public:
    static int nullId;
    Profile();
    int id() const;
    std::string name() const;

    void setId(int id);
    void setName(const std::string& name);

private:
    int m_id;
};

};

#endif
