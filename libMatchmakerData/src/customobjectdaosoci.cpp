#include "customobjectdaosoci.h"
#include "socidbconnection.h"
#include <sstream>
#include <soci.h>
namespace mm{

CustomObjectDaoSoci::CustomObjectDaoSoci(SociDbConnection* sociDbConnection)
{
    m_dbConnection = sociDbConnection;
    m_sociDbConnection = sociDbConnection;
}

bool CustomObjectDaoSoci::load(std::string table, std::string filter, CustomObject* output)
{
    shared_ptr<soci::session> session = m_sociDbConnection->session();
    if(output == 0){
        output = new CustomObject();
    }
    output->setCustomPropertiesLoaded(false);
    string query = "SELECT * FROM " + table + " WHERE " + filter;
    string countQuery = "SELECT count(*) FROM " + table + " WHERE " + filter;
    int rowCount = 0;
     soci::row row;
    try
    {
        *session << countQuery, soci::into(rowCount);
        *session << query, into(row);
    }
    catch(std::exception const & e){
        std::cout << "load error: " << e.what();
        return false;
    }

    if(rowCount == 0){
        return false;
    }



    for( size_t i = 0; i < row.size(); i++){
        soci::indicator ind = row.get_indicator(i);
        soci::column_properties prop = row.get_properties(i);
        std::string colName = prop.get_name();
        soci::data_type colType = prop.get_data_type();

        output->addField(colName);
        if(ind != soci::i_null){
            switch(colType){
            case soci::dt_string:
                output->set<std::string>(colName, row.get<std::string>(i));
                break;
            case soci::dt_double:
                output->set<double>(colName, row.get<double>(i));
                break;
            case soci::dt_integer:
                output->set<int>(colName, row.get<int>(i));
                break;
            case soci::dt_long_long:
                output->set<long long>(colName, row.get<long long>(i));
                break;
            case soci::dt_unsigned_long_long:
                output->set<unsigned long long>(colName, row.get<unsigned long long>(i));
                break;
            case soci::dt_date:
                output->set<std::tm>(colName, row.get<std::tm>(i));
                break;
            }
        }
    }
    output->setCustomPropertiesLoaded(true);
    return true;
}

bool CustomObjectDaoSoci::save(const CustomObject& object, const std::string& table)
{
    return true;
}

}
