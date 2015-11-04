#include <string>
#include <matchmakerdata/profile.h>
#include <gtest/gtest.h>
#include <memory>
//using namespace std;

TEST(Profile, setNameProperty)
{
    mm::Profile profile;
    profile.setName("Rodrigo");
    std::string name = profile.name();
    EXPECT_EQ(name, "Rodrigo");
}
TEST(Profile, nullNameProperty)
{
    mm::Profile profile;
    std::string name = profile.name();
    EXPECT_EQ(name, "");
}
