#include "match.h"

namespace mm
{

Match::Match()
{
    m_id = CustomObject::nullId;
    time_t t = time(0);
    m_creationDateTime = *localtime(&t);
}

int Match::playersCount() const
{
    int totalSize = 0;
    for( auto teamsIterator = m_teams.cbegin(); teamsIterator != m_teams.cend(); teamsIterator++)
    {
        auto team = teamsIterator->second;
        totalSize += team.size();
    }
    return totalSize;
}

int Match::teamsCount() const
{
    return m_teams.size();
}
void Match::addTeamWithId(const std::vector<int>& team, int teamId)
{
    std::cout << "A" << std::endl;
    m_teams[teamId] = team;
    std::cout << "A" << std::endl;
}
int Match::addTeam(const std::vector<int>& team)
{
    std::cout << "B" << std::endl;
    //find the first empty team_id;
    int i = 0;
    while(m_teams.find(i) != m_teams.end())
    {
        i++;
    }
    std::cout << "B" << std::endl;
    addTeamWithId(team, i);
    std::cout << "B id = " << i << std::endl;
    return i;
}

const std::vector<int> Match::team(unsigned int teamId) const
{
    if(m_teams.find(teamId) == m_teams.end())
    {
        std::vector<int> nullVector;
        return nullVector;
    }
    else
    {
        return m_teams.at(teamId);
    }
}

void Match::addPlayer(int playerId, int teamId)
{
    if(m_teams.find(teamId) == m_teams.end())
    {
        addTeamWithId(std::vector<int>(), teamId);
    }
    m_teams[teamId].push_back(playerId);
}

std::tm Match::creationDateTime() const
{
    return m_creationDateTime;
}

void Match::setCreationDateTime(const std::tm& creationDateTime)
{
    m_creationDateTime = creationDateTime;
}
}
