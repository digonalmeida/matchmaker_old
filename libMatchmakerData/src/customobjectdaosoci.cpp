#include "customobjectdaosoci.h"
#include "socidbconnection.h"
namespace mm{

CustomObjectDaoSoci::CustomObjectDaoSoci(SociDbConnection* sociDbConnection)
{
    m_dbConnection = sociDbConnection;
    m_sociDbConnection = sociDbConnection;
}

bool CustomObjectDaoSoci::load(std::string table, std::string filter, CustomObject& output)
{
    return true;
}

bool CustomObjectDaoSoci::save(const CustomObject& object, const std::string& table)
{
    return true;
}

}
