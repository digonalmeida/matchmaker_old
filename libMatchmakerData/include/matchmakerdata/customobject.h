#ifndef MATCHMAKERDATA_H
#define MATCHMAKERDATA_H
#include <boost/optional.hpp>
#include <boost/any.hpp>
#include <boost/cast.hpp>
#include <string>
#include <map>
namespace mm
{
class Unknown_Field {}; //exception
class CustomObject;
typedef boost::optional<boost::any> CustomValue;
};

using namespace mm;

class mm::CustomObject
{
public:
    CustomObject() {}
    ~CustomObject() {}
    CustomValue get(std::string fieldName);
    void addField(std::string fieldName);
    void set(std::string fieldName, boost::any fieldValue);

private:
    std::map<std::string, CustomValue> customFields_;
};
#endif //MATCHMAKERDATA_H
