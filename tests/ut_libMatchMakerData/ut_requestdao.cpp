#include <gtest/gtest.h>
#include <memory>
#include "loadConnection.h"
#include <matchmakerdata/request.h>
#include <matchmakerdata/requestdao.h>

TEST(RequestDao, saveEmpty){
    auto connection = loadConnection();
    auto requestDao = connection->requestDao();

    mm::Request newRequest;
    bool saved = requestDao->saveRequest(newRequest);
    int newRequestId = newRequest.id();
    int idProfile = newRequest.profileId();
    EXPECT_TRUE(saved);
    EXPECT_NE(newRequestId, mm::CustomObject::nullId);
    EXPECT_EQ(idProfile, mm::CustomObject::nullId);

    bool removeu = requestDao->removeRequest(newRequest);
    EXPECT_TRUE(removeu);
}

TEST(RequestDao, load){
    auto connection = loadConnection();
    auto requestDao = connection->requestDao();

    mm::Request newRequest;

    std::time_t currentTime = time(0);
    std::tm newDateTime = *localtime(&currentTime);
    newDateTime.tm_year = 2004;
    std::string newState = "R";
    int newProfileId = 1;

    newRequest.setDateTime(newDateTime);
    newRequest.setState(newState);
    newRequest.setProfileId(newProfileId);

    requestDao->saveRequest(newRequest);
    int newId = newRequest.id();

    mm::Request loadedRequest;
    loadedRequest.setId(newId);

    bool loaded = requestDao->loadRequest(loadedRequest);
    EXPECT_TRUE(loaded);

    int loadedId = loadedRequest.id();
    std::tm loadedDateTime = loadedRequest.dateTime();
    std::string loadedState = loadedRequest.state();
    int loadedProfileId = loadedRequest.profileId();
    EXPECT_EQ(loadedId, newId);
    EXPECT_EQ(newState, loadedState);
    EXPECT_EQ(mktime(&loadedDateTime), mktime(&newDateTime));
    EXPECT_EQ(loadedProfileId, newProfileId);

}
