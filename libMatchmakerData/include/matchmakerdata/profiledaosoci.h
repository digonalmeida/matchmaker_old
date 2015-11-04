#ifndef PROFILEDAOSOCI_H
#define PROFILEDAOSOCI_H

#include "profiledao.h"
#include "customobjectdaosoci.h"

namespace mm{
class ProfileDaoSoci: public ProfileDao, public CustomObjectDaoSoci
{
public:
    ProfileDaoSoci(mm::SociDbConnection* connection);
    bool saveProfile(Profile& profile) override;
    bool loadProfile(Profile& profile) override;
    bool removeProfile(Profile& profile) override;
protected:
private:
    std::string m_table;
};
}

#endif // PROFILEDAOSOCI_H
