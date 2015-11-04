#ifndef MATCHDAO_H
#define MATCHDAO_H

#include "customobjectdao.h"
#include "match.h"

namespace mm
{

class MatchDao : public virtual CustomObjectDao
{
public:
    MatchDao();
    virtual ~MatchDao();

    virtual bool saveMatch(Match& match) = 0;
    virtual bool loadMatch(Match& match) = 0;
    virtual bool removeMatch(Match& match) = 0;

protected:
private:
};

};

#endif // MATCHDAO_H
