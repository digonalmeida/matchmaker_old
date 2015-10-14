#include <matchmakerdata/request.h>
#include <gtest/gtest.h>
#include <string>

TEST(Request, getNullId){
	mm::Request request;
	bool isNull = request.id() == mm::Request::nullId;
	EXPECT_TRUE(isNull);
}

TEST(Request, setId){
	mm::Request request;
	request.setId(10);
	int id = request.id();
	EXPECT_EQUAL(id, 10);
}

TEST(Request, nullProfile){
	mm::Request request;
	std::shared_ptr<mm::Profile> profile = request.profile();
	bool isNull = profile.get() == 0;
	
	EXPECT_TRUE(isNull);
}
TEST(Request, setProfile){
	mm::Request request;
	mm::Profile profileSet;
	profile.setId(10);
	request.setProfile(profileSet);
	
	std::shared_ptr<mm::Profile> profileGet;
	profileGet = request.profile();
	EXPECT_TRUE(profileGet->get() != 0);
	int idProfileGet = profileGet->id();
	EXPECT_EQUAL(profileGet->id(), 10);
}
