#include <string>
#include <matchmakerdata/profile.h>
#include <gtest/gtest.h>
#include <memory>
//using namespace std;

TEST(Profile, getNullId){
	mm::Profile profile;
	bool isNull = profile.id() == mm::Profile::nullId;
	EXPECT_TRUE(isNull);
}

TEST(Profile, setId){
	mm::Profile profile;
	profile.setId(10);
	int id = profile.id();
	EXPECT_EQUAL(id, 10);
}

TEST(Profile, setNameProperty){
	mm::Profile profile;
	profile.addField("name");
	profile.setName("Rodrigo");
	std::string name = profile.name();
	EXPECT_EQUAL(name, "Rodrigo");
}
TEST(Profile, nullNameProperty){
	mm_Profile profile;
	std::string name = profile.name();
	EXPECT_EQUAL(name, "");
}
