#include <string>
#include <matchmakerdata/match.h>
#include <gtest/gtest.h>

TEST(Match, getNullId){
	mm::Match match;
	bool isNull = match.id() == mm::Match::nullId;
	EXPECT_TRUE(isNull);
}

TEST(Match, setId){
	mm::Match match;
	match.setId(10);
	int id = match.id();
	EXPECT_EQUAL(id, 10);
}

TEST(Match, zeroPlayers){
	mm::Match match;
	int playersCount = match.playersCount();
	int teamsCount = match.teamsCount();
	
	EXPECT_TRUE(playersCount == 0);
	EXPECT_TRUE(teamsCount == 0);
}

TEST(Match, setTeam){
	mm::Match match;
	mm::Player playerA, playerB, playerC;
	std::vector< std::shared_ptr<mm::Player> > teamA, teamB;
	playerA.setId(0);
	playerB.setId(1);
	playerC.setId(2);
	match.addPlayer(playerA, 0);
	match.addPlayer(playerB, 1);
	match.addPlayer(playerC, 1);
	
	teamA = match.team(0);
	teamB = match.team(1);
	
	EXPECT_TRUE(teamA.size() == 1);
	EXPECT_TRUE(teamA[0]->id() == 0);
	EXPECT_TRUE(teamB.size() == 2);
	EXPECT_TRUE(teamB[0]->id() == 1);
	
	EXPECT_TRUE(match.teamsCount() == 2);
	EXPECT_TRUE(match.playersCount() == 3);
	
	teamA << playerA;
}
