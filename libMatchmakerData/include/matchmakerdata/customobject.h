#ifndef MATCHMAKERDATA_H
#define MATCHMAKERDATA_H
#include <boost/optional.hpp>
#include <boost/any.hpp>
#include <boost/cast.hpp>
#include <string>
#include <map>
#include <stdexcept>

namespace mm
{
class Unknown_Field {}; //exception
class Null_Field{};

class CustomObject
{
public:
    CustomObject() {}
    ~CustomObject() {}


    void addField(std::string fieldName);

    //throws mm::Unknown_Field and boost::bad_any_cast
    //returns false if value is null
    template<typename T>
    bool get(const std::string fieldName, T &output);

    //throws mm::Unknown_Field
    template<typename T>
    void set(std::string fieldName, T fieldValue);

private:
    std::map<std::string, boost::optional<boost::any> > customFields_;
};

};


template <typename T> bool mm::CustomObject::get(const std::string fieldName, T &output)
{
    boost::optional<boost::any> val;

    try{
        val = customFields_.at(fieldName);
    }
    catch(std::out_of_range error){
        throw mm::Unknown_Field();
    }

    if(!val){
        return false;
    }

    output = boost::any_cast<T>(*val);
    return true;
}

template <typename T> void mm::CustomObject::set(std::string fieldName, T value)
{
    try{
        boost::optional<boost::any> val = customFields_.at(fieldName);
    }
    catch(std::out_of_range error){
        throw mm::Unknown_Field();
    }

    customFields_[fieldName] = boost::any(value);
}
#endif //MATCHMAKERDATA_H
