#ifndef MATCH_H
#define MATCH_H
#include <vector>
#include <map>
#include "customobject.h"

namespace mm
{
class Match : public CustomObject
{
public:
    Match();
    static int nullId;
    int id() const;
    const std::vector<int> team(unsigned int teamId) const;
    int playersCount() const;
    int teamsCount() const;

    void setId(int i);
    void addTeam(const std::vector<int>& team);

private:
    int m_id;
    std::vector< std::vector<int> > m_teams;

};
};

#endif
