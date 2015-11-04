#include <gtest/gtest.h>
#include <memory>
#include "loadConnection.h"
#include <matchmakerdata/match.h>
#include <matchmakerdata/matchdao.h>


TEST(MatchDao, saveEmpty){
    std::shared_ptr<mm::DbConnection> connection;
    connection = loadConnection();
    std::shared_ptr<mm::MatchDao> matchDao = connection->matchDao();
    mm::Match match;
    matchDao->saveMatch(match);
    int savedMatchId = match.id();
    EXPECT_NE(savedMatchId, mm::CustomObject::nullId);

    bool removed = matchDao->removeMatch(match);
    EXPECT_TRUE(removed);
}

TEST(MatchDao, saveDateTime){
    std::shared_ptr<mm::DbConnection> connection;
    connection = loadConnection();
    std::shared_ptr<mm::MatchDao> matchDao = connection->matchDao();
    mm::Match match;
    time_t t = time(0);
    std::tm currentTime = *localtime(&t);
    match.setCreationDateTime(currentTime);
    matchDao->saveMatch(match);

    mm::Match loadedMatch;
    loadedMatch.setId(match.id());
    matchDao->loadMatch(loadedMatch);
    std::tm loadedTime = loadedMatch.creationDateTime();
    EXPECT_EQ(mktime(&loadedTime), mktime(&currentTime));

    bool removed = matchDao->removeMatch(match);
    EXPECT_TRUE(removed);
}

TEST(MatchDao, saveTeams){
    //precisa de um player, id 0
    auto connection = loadConnection();
    mm::Match match;
    vector<int> teamA;
    teamA.push_back(1);
    teamA.push_back(1);
    vector<int> teamB;
    teamB.push_back(1);
    match.addTeam(teamA);
    match.addTeam(teamB);

    auto matchDao = connection->matchDao();
    bool saved = matchDao->saveMatch(match);
    EXPECT_TRUE(saved);

    mm::Match loadedMatch;
    loadedMatch.setId(match.id());
    bool loaded = matchDao->loadMatch(loadedMatch);
    if(!loaded){
        std::cout << "ERRO: " << matchDao->getError() << std::endl;
    }

    EXPECT_TRUE(loaded);

    int playersCount = loadedMatch.playersCount();
    int teamsCount = loadedMatch.teamsCount();

    EXPECT_EQ(3, playersCount);
    EXPECT_EQ(2, teamsCount);

    bool removed = matchDao->removeMatch(match);
    EXPECT_FALSE(removed);//match_profile dependencies

}
