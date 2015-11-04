#include <gtest/gtest.h>
#include <memory>
#include "loadConnection.h"
#include <matchmakerdata/profile.h>
#include <matchmakerdata/profiledao.h>

TEST(ProfileDao, save_remove){
    auto connection = loadConnection();
    auto profileDao = connection->profileDao();

    mm::Profile newProfile;
    std::string nomeTeste = "Nome Teste";
    newProfile.setName(nomeTeste);
    bool saved = profileDao->saveProfile(newProfile);
    EXPECT_TRUE(saved);
    EXPECT_NE(newProfile.id(), mm::CustomObject::nullId);

    bool removed = profileDao->removeProfile(newProfile);
    EXPECT_TRUE(removed);
}

TEST(ProfileDao, load){
    auto connection = loadConnection();
    auto profileDao = connection->profileDao();
    mm::Profile newProfile;
    std::string testName = "Nome Teste Load";
    newProfile.setName(testName);
    profileDao->saveProfile(newProfile);

    mm::Profile loadedProfile;
    loadedProfile.setId(newProfile.id());
    bool loaded = profileDao->loadProfile(loadedProfile);
    EXPECT_TRUE(loaded);
    EXPECT_EQ(newProfile.name(), loadedProfile.name());

    bool removed = profileDao->removeProfile(newProfile);
    EXPECT_TRUE(removed);

    loaded = profileDao->loadProfile(loadedProfile);
    EXPECT_FALSE(loaded);
}
