#include <matchmakerdata/room.h>
#include <gtest/gtest.h>
#include <string>

TEST(Room, setServerAddress)
{
    mm::Room room;
    room.setServerAddress("localhost");
    std::string serverAddress = room.serverAddress();
    EXPECT_EQ(serverAddress, "localhost");
    room.setServerAddress("teste 2");
    EXPECT_EQ(room.serverAddress(), "teste 2");
}

TEST(Room, nullServerAddress)
{
    mm::Room room;
    std::string nullAddress = room.serverAddress();
    EXPECT_EQ(nullAddress, mm::Room::nullAddress);
}
TEST(Room, avaliable)
{
    mm::Room room;
    EXPECT_FALSE(room.available());
    room.setAvailable(false);
    EXPECT_FALSE(room.available());
    room.setAvailable(true);
    EXPECT_TRUE(room.available());
}
