#include <matchmakingdata/room.h>
#include <gtest/gtest.h>
#include <string>

TEST(Room, getNullId){
	mm::Room room;
	bool isNull = room.id() == mm::Room::nullId;
	EXPECT_TRUE(isNull);
}

TEST(Room, setId){
	mm::Room room;
	room.setId(10);
	int id = room.id();
	EXPECT_EQUAL(id, 10);
}

TEST(Room, setServerAddress){
	mm::Room room;
	room.setServerAddress("localhost");
	std::string serverAddress = room.serverAddress();
	EXPECT_EQUAL(serverAddress, "localhost");
	room.setServerAddress("teste 2");
	EXPECT_EQUAL(room.serverAddress() == "teste 2");
}

TEST(Room, nullServerAddress){
	mm::Room room;
	std::string nullAddress = room.serverAddress();
	EXPECT_EQUAL(nullAddresss, mm::Room::nullAddress);
}
TEST(Room, avaliable){
	mm::Room room;
	EXPECT_FALSE(room.avaliable());
	room.setAvailable(false);
	EXPECT_FALSE(room.available());
	room.setAvailable(true);
	EXPECT_TRUE(room.available());
}
