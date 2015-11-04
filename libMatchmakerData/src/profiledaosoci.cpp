#include "profiledaosoci.h"

namespace mm
{

ProfileDaoSoci::ProfileDaoSoci(mm::SociDbConnection* connection)
    : CustomObjectDaoSoci(connection)
{
    //ctor
    m_table = "profile";
}

bool ProfileDaoSoci::saveProfile(Profile& profile)
{
    profile.addField("name");
    profile.set<std::string>("name", profile.name());

    bool salvou = saveCustomProperties(m_table, profile);
    return salvou;
}
bool ProfileDaoSoci::loadProfile(Profile& profile)
{
    bool loaded = loadCustomProperties(m_table, profile);
    profile.setName("");
    if(!profile.isNull("name")){
        profile.setName(profile.get<std::string>("name"));
    }
    return loaded;
}
bool ProfileDaoSoci::removeProfile(Profile& profile)
{
    bool removed = ProfileDao::remove(m_table, profile);
    return removed;
}

};
