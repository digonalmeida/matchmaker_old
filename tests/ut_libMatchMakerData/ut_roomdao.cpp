#include <gtest/gtest.h>
#include <memory>
#include "loadConnection.h"
#include <matchmakerdata/room.h>
#include <matchmakerdata/roomdao.h>

TEST(RoomDao, saveEmpty){
    auto connection = loadConnection();
    auto roomDao = connection->roomDao();

    mm::Room newRoom;
    bool saved = roomDao->saveRoom(newRoom);
    int newRoomId = newRoom.id();
    int idMatch = newRoom.matchId();
    EXPECT_TRUE(saved);
    EXPECT_NE(newRoomId, mm::CustomObject::nullId);
    EXPECT_EQ(idMatch, mm::CustomObject::nullId);

    bool removeu = roomDao->removeRoom(newRoom);
    EXPECT_TRUE(removeu);
}

TEST(RoomDao, load){
    auto connection = loadConnection();
    auto roomDao = connection->roomDao();

    mm::Room newRoom;

    std::string newServer;
    int newMatchId = 1;

    newRoom.setServerAddress(newServer);
    newRoom.setMatchId(newMatchId);

    roomDao->saveRoom(newRoom);
    int newId = newRoom.id();

    mm::Room loadedRoom;
    loadedRoom.setId(newId);

    bool loaded = roomDao->loadRoom(loadedRoom);
    EXPECT_TRUE(loaded);

    int loadedId = loadedRoom.id();
    std::string loadedServer = loadedRoom.serverAddress();
    int loadedMatchId = loadedRoom.matchId();

    EXPECT_EQ(loadedId, newId);
    EXPECT_EQ(newServer, loadedServer);
    EXPECT_EQ(loadedMatchId, newMatchId);

}
