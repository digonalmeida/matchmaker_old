#include "../include/matchmakerdata/customobject.h"

using namespace mm;
void mm::CustomObject::addField(std::string fieldName)
{
    customFields_[fieldName] = boost::none;
}




