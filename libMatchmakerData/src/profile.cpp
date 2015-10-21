#include "profile.h"

namespace mm
{

int Profile::nullId = 0;

Profile::Profile()
{
    m_id = Profile::nullId;
}

int Profile::id() const
{
    return m_id;
}

void Profile::setId(int id)
{
    m_id = id;
}

std::string Profile::name() const
{
    if(contains("name"))
    {
        if(!isNull("name"))
        {
            return get<std::string>("name");
        }
    }
    return "";
}

void Profile::setName(const std::string& name)
{
    set<std::string>("name", name);
}

}
