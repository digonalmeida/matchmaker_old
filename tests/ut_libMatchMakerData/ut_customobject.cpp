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
    EXPECT_THROW(customObject.get<std::string>("field", s), mm::Unknown_Field);
    customObject.addField("field");
    EXPECT_FALSE(customObject.get<std::string>("field", s));
}

TEST(CustomObject, setValue){

    mm::CustomObject customObject;
    customObject.addField("field");

    customObject.set<std::string>("field", "teste");
    std::string fieldValue;
    bool getWorked = customObject.get<std::string>("field", fieldValue);

    EXPECT_TRUE(getWorked);

    EXPECT_EQ(fieldValue, std::string("teste"));
}

TEST(CustomObject, getNullValue){
    mm::CustomObject customObject;
    customObject.addField("field");
    std::string fieldValue;
    bool worked = customObject.get<std::string>("field", fieldValue);
    EXPECT_FALSE(worked);
}

TEST(CustomObject, getValue){
    mm::CustomObject customObject;
    customObject.addField("field");
    customObject.set<std::string>("field", "valor");
    std::string fieldValue;
    bool worked = customObject.get<std::string>("field", fieldValue);
    EXPECT_TRUE(worked);
    EXPECT_EQ(fieldValue, std::string("valor"));
}

TEST(Boost, optionalNull){
    boost::optional<boost::any> c = boost::none;
    EXPECT_FALSE(c);
}
