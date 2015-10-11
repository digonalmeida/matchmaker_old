#include <iostream>
#include <string>
#include <matchmakerdata/customobject.h>
#include <boost/any.hpp>
#include <boost/cast.hpp>
#include <gtest/gtest.h>
#include <boost/optional.hpp>
#include <exception>
//using namespace std;

TEST (CustomObject, addField) {
    mm::CustomObject customObject;
    std::string s;
    EXPECT_FALSE(customObject.contains("field"));
    customObject.addField("field");
    EXPECT_TRUE(customObject.contains("field"));
}

TEST(CustomObject, setValue){

    mm::CustomObject customObject;
    customObject.addField("field");

    customObject.set<std::string>("field", "teste");

    std::string fieldValue = customObject.value<std::string>("field");

    EXPECT_EQ(fieldValue, std::string("teste"));
}

TEST(CustomObject, getNullValue){

    mm::CustomObject customObject;
    customObject.addField("field");
    EXPECT_TRUE(customObject.contains("field"));
    EXPECT_TRUE(customObject.isNull("field"));
    EXPECT_THROW(customObject.value<std::string>("field"), mm::Null_Field);
}

TEST(CustomObject, getValue){
    mm::CustomObject customObject;
    customObject.addField("field");
    customObject.set<std::string>("field", "valor");
    std::string fieldValue = customObject.value<std::string>("field");
    EXPECT_EQ(fieldValue, std::string("valor"));
}

TEST(Boost, optionalNull){
    boost::optional<boost::any> c = boost::none;
    EXPECT_FALSE(c);
}
