#include <matchmakerdata/request.h>
#include <gtest/gtest.h>
#include <string>
#include <memory>

TEST(Request, nullProfile)
{
    mm::Request request;
    int profileId = request.profileId();

    EXPECT_TRUE(profileId == mm::Profile::nullId);
}
TEST(Request, setProfile)
{
    mm::Request request;
    int profileIdSet = 10;

    request.setProfileId(profileIdSet);
    int profileIdGet = request.profileId();

    EXPECT_EQ(10, profileIdSet);
}
