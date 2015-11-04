#include "customobjectdao.h"
#include <sstream>

namespace mm
{
bool CustomObjectDao::loadCustomPropertiesWithId(const std::string& table, int id, CustomObject& output)
{
    std::stringstream filter;
    filter << "id = " << id << " ";
    return loadCustomPropertiesWithFilter(table, filter.str(), output);
}

bool CustomObjectDao::loadCustomProperties(const std::string& table, CustomObject& output)
{

    if(output.id() == CustomObject::nullId)
    {
        m_error = "Object not found";
        return false;
    }
    else
    {
        return loadCustomPropertiesWithId(table, output.id(), output);
    }

    return false;
}

bool CustomObjectDao::saveCustomProperties(const std::string& table, CustomObject& object)
{
    if(object.id() == CustomObject::nullId)
    {
        return insertObject(table, object);
    }
    else
    {
        return updateObject(table, object);
    }
}

std::vector<CustomObject> CustomObjectDao::queryCustomObject(const std::string& table, const std::string& filter, int max, bool* ok)
{
    auto ids = queryIds(table, filter, max, ok);
    std::vector<CustomObject> customObjects;
    for(size_t i = 0; i < ids.size(); i++){
        int id = ids.at(i);
        CustomObject customObject;
        customObject.setId(id);
        if(!loadCustomPropertiesWithId(table, id, customObject))
        {
            if(ok != 0){
                *ok = false;
                return std::vector<CustomObject>();
            }
        }
    }
    return customObjects;
}


bool CustomObjectDao::remove(const std::string& table, int id)
{
    std::stringstream filter;
    filter << "id = " << id << " ";
    return remove(table, filter.str());
}
bool CustomObjectDao::remove(const std::string& table, CustomObject& object)
{


    object.setCustomPropertiesLoaded(false);
    if(object.id() == CustomObject::nullId)
    {
        m_error = "[CustomObjectDao::remove] object not found";
        return false;
    }
    else
    {
        bool removed = remove(table, object.id());
        object.setId(CustomObject::nullId);
        return removed;
    }
}

}
