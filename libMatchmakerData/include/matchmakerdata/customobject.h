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
class Null_Field {};

class CustomObject
{
public:
    CustomObject() {
        m_customPropertiesLoaded = false;
    }
    ~CustomObject() {}

    void addField(const std::string &fieldName);
    bool contains(const std::string &fieldName) const;
    bool isNull(const std::string &fieldName) const;
    bool customPropertiesLoaded() const {
        return m_customPropertiesLoaded;
    };
    void setCustomPropertiesLoaded(bool b){
        m_customPropertiesLoaded = b;
    }

    //throws mm::Unknown_Field and boost::bad_any_cast
    //returns false if value is null
    template<typename T> T value(const std::string &fieldName) const;
    template<typename T> T get(const std::string &fieldName) const
    {
        return value<T>(fieldName);
    };

    //throws mm::Unknown_Field
    template<typename T>
    void set(const std::string &fieldName, T fieldValue);

protected:
    std::map<std::string, boost::optional<boost::any> > m_customFields;
    bool m_customPropertiesLoaded;
};



template <typename T> T CustomObject::value(const std::string &fieldName) const
{
    boost::optional<boost::any> val;
    T output;

    if(!contains(fieldName))
    {
        throw mm::Unknown_Field();
    }
    if(isNull(fieldName))
    {
        throw mm::Null_Field();
    }

    val = m_customFields.at(fieldName);

    output = boost::any_cast<T>(*val);
    return output;
}

template <typename T> void CustomObject::set(const std::string &fieldName, T value)
{
    try
    {
        boost::optional<boost::any> val = m_customFields.at(fieldName);
    }
    catch(std::out_of_range error)
    {
        throw mm::Unknown_Field();
    }

    m_customFields[fieldName] = boost::any(value);
}

}
#endif //MATCHMAKERDATA_H
