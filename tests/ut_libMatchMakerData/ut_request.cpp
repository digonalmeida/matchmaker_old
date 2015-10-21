#include <matchmakerdata/request.h>
#include <gtest/gtest.h>
#include <string>
#include <memory>

TEST(Request, getNullId){
	mm::Request request;
	bool isNull = request.id() == mm::Request::nullId;
	EXPECT_TRUE(isNull);
}

TEST(Request, setId){
	mm::Request request;
	request.setId(10);
	int id = request.id();
	EXPECT_EQ(id, 10);
}

TEST(Request, nullProfile){
	mm::Request request;
	int profileId = request.profileId();

	EXPECT_TRUE(profileId == mm::Profile::nullId);
}
TEST(Request, setProfile){
	mm::Request request;
	int profileIdSet = 10;

	request.setProfileId(profileIdSet);
	int profileIdGet = request.profileId();

	EXPECT_EQ(10, profileIdSet);
}
