#include "match.h"

namespace mm
{
int Match::nullId = -1;
Match::Match()
{
    m_id = Match::nullId;
}

int Match::id() const
{
    return m_id;
}

void Match::setId(int id)
{
    m_id = id;
}

int Match::playersCount() const
{
    int totalSize = 0;
    for( auto teamsIterator = m_teams.cbegin(); teamsIterator != m_teams.cend(); teamsIterator++)
    {
        auto team = *teamsIterator;
        totalSize += team.size();
    }
    return totalSize;
}

int Match::teamsCount() const
{
    return m_teams.size();
}

void Match::addTeam(const std::vector<int>& team)
{
    m_teams.push_back(team);
}

const std::vector<int> Match::team(unsigned int teamId) const
{
    if(teamId >= m_teams.size())
    {
        std::vector<int> nullVector;
        return nullVector;
    }
    else
    {
        return m_teams.at(teamId);
    }
}
}
