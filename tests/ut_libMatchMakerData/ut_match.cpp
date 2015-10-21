#include <string>
#include <matchmakerdata/profile.h>
#include <matchmakerdata/match.h>
#include <gtest/gtest.h>
#include <memory>

TEST(Match, getNullId){
	mm::Match match;
	bool isNull = match.id() == mm::Match::nullId;
	EXPECT_TRUE(isNull);
}

TEST(Match, setId){
	mm::Match match;
	match.setId(10);
	int id = match.id();
	EXPECT_EQ(id, 10);
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
	mm::Profile playerA, playerB, playerC;
	std::vector<int> teamAInput, teamBInput, teamA, teamB;

    teamAInput.push_back(1);
    teamBInput.push_back(2);
    teamBInput.push_back(3);

    match.addTeam(teamAInput);
    match.addTeam(teamBInput);

	teamA = match.team(0);
	teamB = match.team(1);

	EXPECT_EQ(1, teamA.size());
	EXPECT_EQ(1, teamA[0]);
	EXPECT_EQ(2, teamB.size());
	EXPECT_EQ(2, teamB[0]);
	EXPECT_EQ(3, teamB[1]);

	EXPECT_EQ(2, match.teamsCount());
	EXPECT_EQ(3, match.playersCount());
}
