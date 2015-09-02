#include <iostream>
#include <string>
#include <matchmakerdata/customobject.h>
#include <boost/any.hpp>
#include <boost/cast.hpp>
#include <gtest/gtest.h>
#include <boost/optional.hpp>
//using namespace std;

TEST (CustomObject, addField) {
    mm::CustomObject customObject;
    EXPECT_THROW(customObject.get<std::string>("field"), mm::Unknown_Field);
    customObject.addField("field");
    EXPECT_FALSE(customObject.get<std::string>("field"));
}

TEST(CustomObject, setValue){

    mm::CustomObject customObject;
    customObject.addField("field");

    customObject.set<std::string>("field", "teste");
    boost::optional<std::string> fieldValue;
    fieldValue = customObject.get<std::string>("field");

    EXPECT_TRUE(fieldValue);

    EXPECT_EQ(boost::any_cast<std::string>(*fieldValue).c_str(), std::string("teste"));
}

TEST(CustomObject, getNullValue){
    mm::CustomObject customObject;
    customObject.addField("field");
    boost::optional<std::string> fieldValue = customObject.get<std::string>("field");
    EXPECT_FALSE(fieldValue);
}

TEST(CustomObject, getValue){
    mm::CustomObject customObject;
    customObject.addField("field");
    customObject.set<std::string>("field", "valor");
    boost::optional<std::string> fieldValue = customObject.get<std::string>("field");
    std::string strValue = *fieldValue;
    EXPECT_TRUE(fieldValue);
    EXPECT_EQ(strValue, std::string("valor"));
}

TEST(Boost, optionalNull){
    boost::optional<boost::any> c = boost::none;
    EXPECT_FALSE(c);
}
