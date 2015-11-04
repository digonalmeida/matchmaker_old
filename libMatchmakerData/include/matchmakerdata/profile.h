#include <string>
#include "customobject.h"
#ifndef PROFILE_H
#define PROFILE_H

namespace mm
{

class Profile : public CustomObject
{
public:
    Profile();
    std::string name() const;

    void setName(const std::string& name);

private:
    std::string m_name;
};

};

#endif
