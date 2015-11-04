#ifndef PROFILEDAO_H
#define PROFILEDAO_H

#include "profile.h"
#include "customobjectdao.h"

namespace mm{
class ProfileDao : public virtual CustomObjectDao
{
public:
    ProfileDao();
    virtual ~ProfileDao();
    virtual bool saveProfile(Profile& profile) = 0;
    virtual bool loadProfile(Profile& profile) = 0;
    virtual bool removeProfile(Profile& profile) = 0;


protected:
private:
};
};
#endif // PROFILEDAO_H
