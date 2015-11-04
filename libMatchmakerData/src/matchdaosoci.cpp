#include "matchdaosoci.h"
namespace mm
{

MatchDaoSoci::MatchDaoSoci(mm::SociDbConnection* sociConnection)
    : CustomObjectDaoSoci(sociConnection)
{
    m_table = "match";
    m_matchProfileTable = "match_profile";
    //ctor
}
bool MatchDaoSoci::saveMatch(Match& match)
{
    if(!match.contains("creation_date_time")){
        match.addField("creation_date_time");
    }
    match.set<std::tm>("creation_date_time", match.creationDateTime());
    bool salvou = saveCustomProperties(m_table, match);
    if(salvou){
        bool salvouTeams = saveTeams(match);
        if(salvouTeams){
            return true;
        }
    }

    return false;
}

bool MatchDaoSoci::saveTeams(Match& match)
{
    std::cout << "------------ Match id" << match.id()  << "------------";
    unsigned int teamsCount = match.teamsCount();

    for(unsigned int teamId = 0; teamId < teamsCount; teamId++)
    {
        vector<int> team = match.team(teamId);
        CustomObject matchProfile;
        matchProfile.addField("id");
        matchProfile.addField("team");
        matchProfile.addField("id_match");
        matchProfile.addField("id_profile");
        matchProfile.set<int>("id_match", match.id());
        matchProfile.set<int>("team", teamId);

        for(size_t i = 0; i < team.size(); i++){
            int idProfile = team[i];
            matchProfile.setId(CustomObject::nullId);
            matchProfile.set<int>("id_profile", idProfile);
            if(!saveCustomProperties(m_matchProfileTable, matchProfile)){
                m_error = "Couldn't save team from match. " + m_error;
                return false;
            }
        }
    }
    return true;
}

bool MatchDaoSoci::loadMatch(Match& match)
{
    bool loaded = loadCustomProperties(m_table, (CustomObject&) match);
    match.setCreationDateTime(match.get<std::tm>("creation_date_time"));
    if(loaded){
        bool loadedTeams = loadTeams(match);
        if(loadedTeams){
            return true;
        }
    }
    return false;
}

bool MatchDaoSoci::loadTeams(Match& match)
{
    std::stringstream filter;
    filter << "id_match = " << match.id();
    bool ok;
    auto ids = queryIds(m_matchProfileTable, filter.str() , 100, &ok);
    if(!ok){
        m_error = "couldn't load match teams; " + m_error;
        return false;
    }
    if(ok){
        for(size_t i = 0; i < ids.size(); i++)
        {
            int matchProfileId = ids[i];
            CustomObject matchProfile;
            matchProfile.setId(matchProfileId);

            bool loaded = loadCustomProperties(m_matchProfileTable, matchProfile);
            if(loaded){
                bool hasProfile = matchProfile.contains("id_profile");
                bool hasTeam = matchProfile.contains("team");
                if(hasProfile && hasTeam)
                {
                    bool nullProfile = matchProfile.isNull("id_profile");
                    bool nullTeam = matchProfile.isNull("team");
                    if(!nullProfile && ! nullTeam){
                        int id_profile = matchProfile.get<int>("id_profile");
                        int id_team = matchProfile.get<int>("team");
                        match.addPlayer(id_profile, id_team);
                    }
                    else if(nullProfile){
                        m_error = "loaded match_profile with null profile";
                        return false;
                    }
                    else if(nullTeam){
                        m_error = "loaded match_profile with null team";
                        return false;
                    }
                }
                else
                {
                    m_error = "match_profile loaded without profile or team";
                    return false;
                }
            }
        }
        return true;
    }
    return false;
}
bool MatchDaoSoci::removeMatch(Match& match)
{
    bool removeu = MatchDao::remove(m_table,(CustomObject&) match);
    return removeu;
}
};
