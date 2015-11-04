#include "profile.h"

namespace mm
{

Profile::Profile()
{
    m_id = Profile::nullId;
}

std::string Profile::name() const
{
    return m_name;
}

void Profile::setName(const std::string& name)
{
    m_name = name;
}

}
