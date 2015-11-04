#ifndef CUSTOMOBJECT_H
#define CUSTOMOBJECT_H
#include <boost/optional.hpp>
#include <boost/any.hpp>
#include <boost/cast.hpp>
#include <string>
#include <map>
#include <stdexcept>
#include <ctime>

namespace mm
{

class Unknown_Field {}; //exception
class Null_Field {};

class CustomObject
{
public:
    static int nullId;
    enum CustomFieldType
    {
        FIELD_TYPE_UNKNOWN,
        FIELD_TYPE_STRING,
        FIELD_TYPE_INT,
        FIELD_TYPE_DOUBLE,
        FIELD_TYPE_DATE_TIME,
        FIELD_TYPE_LONG,
        FIELD_TYPE_LONG_LONG,
        FIELD_TYPE_UNSIGNED_LONG_LONG
    };
    CustomObject()
    {
        m_id = CustomObject::nullId;
        m_customPropertiesLoaded = false;
    }
    ~CustomObject() {}

    void addField(const std::string &fieldName);
    void setNull(const std::string &fileName);
    bool contains(const std::string &fieldName) const;
    bool isNull(const std::string &fieldName) const;
    bool customPropertiesLoaded() const;
    void setCustomPropertiesLoaded(bool b);

    int id();
    void setId(int id);


    //throws mm::Unknown_Field and boost::bad_any_cast
    //returns false if value is null
    template<typename T> T value(const std::string &fieldName) const;
    template<typename T> T get(const std::string &fieldName) const ;

    //throws mm::Unknown_Field
    template<typename T>
    void set(const std::string &fieldName, T fieldValue);

    typedef boost::optional< boost::any > CustomField;
    typedef std::map<std::string, CustomField > CustomFieldMap;

    const CustomFieldMap& customFields() const
    {
        return m_customFields;
    }

    CustomFieldType getFieldType(std::string fieldName)
    {
        if(m_customFieldTypes.find(fieldName) != m_customFieldTypes.end())
        {
            return m_customFieldTypes[fieldName];
        }
        else
        {
            return FIELD_TYPE_UNKNOWN;
        }
    }
    void setFieldType(std::string fieldName, CustomFieldType fieldType)
    {
        m_customFieldTypes[fieldName] = fieldType;
    }

protected:
    CustomFieldMap m_customFields;
    std::map<std::string, CustomFieldType> m_customFieldTypes;
    bool m_customPropertiesLoaded;
    int m_id;

private:

    template<typename T> CustomFieldType fieldType()
    {
        std::cout << "foi o padrão pqp";
        return FIELD_TYPE_UNKNOWN;
    }

};
template<> CustomObject::CustomFieldType CustomObject::fieldType<std::string>();
template<> CustomObject::CustomFieldType CustomObject::fieldType<int>();
template<> CustomObject::CustomFieldType CustomObject::fieldType<double>();
template<> CustomObject::CustomFieldType CustomObject::fieldType<long long>();
template<> CustomObject::CustomFieldType CustomObject::fieldType<unsigned long long>();
template<> CustomObject::CustomFieldType CustomObject::fieldType<std::tm>();

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
    //std::cout << "setting " << fieldName << std::endl;
    try
    {
        boost::optional<boost::any> val = m_customFields.at(fieldName);
    }
    catch(std::out_of_range error)
    {
        throw mm::Unknown_Field();
    }

    m_customFields[fieldName] = boost::any(value);
    setFieldType(fieldName, fieldType<T>());
}

template<typename T> T CustomObject::get(const std::string &fieldName) const
{
    return value<T>(fieldName);
};

};
#endif //CUSTOMOBJECT_H
