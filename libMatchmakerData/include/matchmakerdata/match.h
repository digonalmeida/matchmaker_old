#ifndef MATCH_H
#define MATCH_H
#include <vector>
#include <map>
#include "customobject.h"
#include <ctime>

namespace mm
{
class Match : public CustomObject
{
public:
    Match();

    const std::vector<int> team(unsigned int teamId) const;
    int playersCount() const;
    int teamsCount() const;
    std::tm creationDateTime() const;

    //returns new team id
    int addTeam(const std::vector<int>& team);
    void addTeamWithId(const std::vector<int>& team, int teamId);
    void addPlayer(int playerId, int teamId);
    void setCreationDateTime(const std::tm& creationDateTime);

private:
    //team_id, team
    std::map<int, std::vector<int> > m_teams;
    std::tm m_creationDateTime;

};
};

#endif
