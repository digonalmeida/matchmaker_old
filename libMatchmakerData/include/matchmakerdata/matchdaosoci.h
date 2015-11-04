#ifndef MATCHDAOSOCI_H
#define MATCHDAOSOCI_H


#include "matchdao.h"
#include "customobjectdaosoci.h"

namespace mm
{

class MatchDaoSoci : public virtual MatchDao, public CustomObjectDaoSoci
{
public:
    MatchDaoSoci(mm::SociDbConnection* sociConnection);
    bool saveMatch(Match& match);
    bool loadMatch(Match& match);
    bool removeMatch(Match& match);
protected:
    bool saveTeams(Match& match);
    bool loadTeams(Match& match);
private:
    std::string m_table;
    std::string m_matchProfileTable;
};

};
#endif // MATCHDAOSOCI_H
