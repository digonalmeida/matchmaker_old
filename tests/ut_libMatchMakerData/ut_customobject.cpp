#include <iostream>
#include <string>
#include <matchmakerdata/customobject.h>
#include <boost/any.hpp>
#include <boost/cast.hpp>
#include <gtest/gtest.h>
#include <boost/optional.hpp>
#include <exception>
//using namespace std;

TEST(CustomObject, getNullId)
{
    mm::CustomObject customObject;
    bool isNull = customObject.id() == mm::CustomObject::nullId;
    EXPECT_TRUE(isNull);
}

TEST(Match, setId)
{
    mm::CustomObject customObject;
    customObject.setId(10);
    int id = customObject.id();
    EXPECT_EQ(id, 10);
}

TEST (CustomObject, addField)
{
    mm::CustomObject customObject;
    std::string s;
    EXPECT_FALSE(customObject.contains("field"));
    customObject.addField("field");
    EXPECT_TRUE(customObject.contains("field"));
}

TEST(CustomObject, setValue)
{

    mm::CustomObject customObject;
    customObject.addField("field");

    customObject.set<std::string>("field", "teste");

    std::string fieldValue = customObject.value<std::string>("field");

    EXPECT_EQ(fieldValue, std::string("teste"));
}


TEST(CustomObject, getNullValue)
{

    mm::CustomObject customObject;
    customObject.addField("field");
    EXPECT_TRUE(customObject.contains("field"));
    EXPECT_TRUE(customObject.isNull("field"));
    EXPECT_THROW(customObject.value<std::string>("field"), mm::Null_Field);
}

TEST(CustomObject, getValue)
{
    mm::CustomObject customObject;
    customObject.addField("field");
    customObject.set<std::string>("field", "valor");
    std::string fieldValue = customObject.value<std::string>("field");
    EXPECT_EQ(fieldValue, std::string("valor"));
}

TEST(Boost, optionalNull)
{
    boost::optional<boost::any> c = boost::none;
    EXPECT_FALSE(c);
}

TEST (CustomObject, fieldType)
{
    mm::CustomObject customObject;

    customObject.addField("name");
    customObject.set<std::string>("name", "teste");
    EXPECT_EQ(mm::CustomObject::FIELD_TYPE_STRING, customObject.getFieldType("name"));
}
