#include "../include/matchmakerdata/customobject.h"

namespace mm
{
int CustomObject::nullId = -1;

void CustomObject::addField(const std::string &fieldName)
{
    m_customFields[fieldName] = boost::none;
}

void CustomObject::setNull(const std::string &fileName)
{
    addField(fileName);
}
bool CustomObject::customPropertiesLoaded() const
{
    return m_customPropertiesLoaded;
}
void CustomObject::setCustomPropertiesLoaded(bool b)
{
    m_customPropertiesLoaded = b;
}

bool CustomObject::contains(const std::string &fieldName) const
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

bool CustomObject::isNull(const std::string &fieldName) const
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

int CustomObject::id()
{
    return m_id;
}
void CustomObject::setId(int id)
{
    m_id = id;
}

template<> CustomObject::CustomFieldType CustomObject::fieldType<std::string>()
{
//std::cout << "setou string!";
    return FIELD_TYPE_STRING;
}
template<> CustomObject::CustomFieldType CustomObject::fieldType<int>()
{

    return FIELD_TYPE_INT;
}
template<> CustomObject::CustomFieldType CustomObject::fieldType<double>()
{
    return FIELD_TYPE_DOUBLE;
}
template<> CustomObject::CustomFieldType CustomObject::fieldType<long long>()
{
    return FIELD_TYPE_LONG_LONG;
}
template<> CustomObject::CustomFieldType CustomObject::fieldType<unsigned long long>()
{
    return FIELD_TYPE_UNSIGNED_LONG_LONG;
}
template<> CustomObject::CustomFieldType CustomObject::fieldType<std::tm>()
{
    return FIELD_TYPE_DATE_TIME;
}
}

