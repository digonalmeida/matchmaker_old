#include "../include/matchmakerdata/customobject.h"
#include <stdexcept>
using namespace mm;
void mm::CustomObject::addField(std::string fieldName)
{
    //CustomValue customValue = boost::none;

    customFields_[fieldName] = boost::none;
    //customFields_.insert(std::pair<std::string, CustomValue>(fieldName, boost::none));
}

mm::CustomValue mm::CustomObject::get(std::string fieldName)
{
    CustomValue val;

    try{
        val = customFields_.at(fieldName);
    }
    catch(std::out_of_range error){
        throw mm::Unknown_Field();
    }

    return val;
}

void mm::CustomObject::set(std::string fieldName, boost::any value)
{
    try{
        CustomValue val = customFields_.at(fieldName);
    }
    catch(std::out_of_range error){
        throw mm::Unknown_Field();
    }
    customFields_[fieldName].reset();
    customFields_[fieldName] = CustomValue(value);
}
