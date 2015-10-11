#include "../include/matchmakerdata/customobject.h"
using namespace mm;

void mm::CustomObject::addField(const std::string &fieldName)
{
    m_customFields[fieldName] = boost::none;
}

bool mm::CustomObject::contains(const std::string &fieldName) const
{
    if(m_customFields.find(fieldName) != m_customFields.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool mm::CustomObject::isNull(const std::string &fieldName) const
{

    if(!contains(fieldName))
    {
        return true;
    }

    boost::optional<boost::any> fieldValue = m_customFields.at(fieldName);
    if(!fieldValue)
    {
        return true;
    }
    else
    {
        return false;
    }

}

