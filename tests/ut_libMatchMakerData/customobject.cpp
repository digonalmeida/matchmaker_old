#include <iostream>
#include <string>
//#include <matchmakerData/customobject.h>
#include <boost/any.hpp>
#include <boost/cast.hpp>
#include <gtest/gtest.h>
#include <boost/optional.hpp>
//using namespace std;

typedef boost::optional<boost::any> customtype;

TEST (b, anyInt) {

    customtype i;
    i = 10;
    int b = boost::any_cast<int>(*i);
    //std::string b = boost::any_cast<int>(i);
    EXPECT_EQ (b, 10);
}

