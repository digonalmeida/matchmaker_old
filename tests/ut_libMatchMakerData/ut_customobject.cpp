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
    EXPECT_THROW(customObject.get("field"), mm::Unknown_Field);
    customObject.addField("field");
    mm::CustomValue field;
    EXPECT_NO_THROW(field = customObject.get("field"));
}

TEST(CustomObject, setValue){

    mm::CustomObject customObject;
    customObject.addField("field");

    customObject.set("field", std::string("teste"));
    mm::CustomValue fieldValue;

    EXPECT_NO_THROW(fieldValue = customObject.get("field"));

    EXPECT_TRUE(fieldValue);

    EXPECT_EQ(boost::any_cast<std::string>(*fieldValue), std::string("teste"));
}

TEST(CustomObject, getNullValue){
    mm::CustomObject customObject;
    customObject.addField("field");
    customObject.set("field", boost::none);
    mm::CustomValue fieldValue = customObject.get("field");
    EXPECT_FALSE(fieldValue);
}

TEST(CustomObject, getValue){
    mm::CustomObject customObject;
    customObject.addField("field");
    customObject.set("field", std::string("valor"));
    mm::CustomValue fieldValue = customObject.get("field");
    std::string strValue = boost::any_cast<std::string>(*fieldValue);
}
TEST(Boost, optionalNull){
    mm::CustomValue c = boost::none;
    EXPECT_FALSE(c);
}
