#include "customobjectdaosoci.h"
#include "socidbconnection.h"
#include <sstream>
#include <soci.h>
#include <list>
#include <map>
#include <ctime>

namespace mm
{

CustomObjectDaoSoci::CustomObjectDaoSoci(SociDbConnection* sociDbConnection)
{
    m_dbConnection = sociDbConnection;
    m_sociDbConnection = sociDbConnection;
}
std::vector<int> CustomObjectDaoSoci::queryIds(const std::string& table, const std::string& filter, int max, bool* ok)
{
    bool _ok = true;
    std::vector<int> ids(max);
    auto session = m_sociDbConnection->session();
    try{
        *session << "SELECT id FROM " << table << " WHERE " << filter, soci::into(ids);
    }
    catch(const std::exception & e){
        m_error = e.what();
        _ok = false;
    }

    if(ok != 0){
        *ok = _ok;
    }

    if(_ok){
        return ids;
    }
    else{
        return std::vector<int>();
    }
}
bool CustomObjectDaoSoci::loadCustomPropertiesWithFilter(const std::string& table, const std::string& filter, CustomObject& output)
{
    shared_ptr<soci::session> session = m_sociDbConnection->session();
    output.setId(-1);

    output.setCustomPropertiesLoaded(false);
    string query = "SELECT * FROM " + table + " WHERE " + filter;
    string countQuery = "SELECT count(*) FROM " + table + " WHERE " + filter;

    int rowCount = 0;
    soci::row row;
    try
    {
        *session << countQuery, soci::into(rowCount);
        *session << query, into(row);
    }
    catch(std::exception const & e)
    {
        m_error = std::string("load error: ") + e.what();
        return false;
    }

    if(rowCount == 0)
    {
        m_error = "object not found";
        return false;
    }



    for( size_t i = 0; i < row.size(); i++)
    {
        soci::indicator ind = row.get_indicator(i);
        soci::column_properties prop = row.get_properties(i);
        std::string colName = prop.get_name();
        soci::data_type colType = prop.get_data_type();

        output.addField(colName);
        if(ind != soci::i_null)
        {
            switch(colType)
            {
            case soci::dt_string:
                output.set<std::string>(colName, row.get<std::string>(i));
                break;
            case soci::dt_double:
                output.set<double>(colName, row.get<double>(i));
                break;
            case soci::dt_integer:
                output.set<int>(colName, row.get<int>(i));
                break;
            case soci::dt_long_long:
                output.set<long long>(colName, row.get<long long>(i));
                break;
            case soci::dt_unsigned_long_long:
                output.set<unsigned long long>(colName, row.get<unsigned long long>(i));
                break;
            case soci::dt_date:
                output.set<std::tm>(colName, row.get<std::tm>(i));
                break;
            }
        }
    }
    if(output.contains("id"))
    {
        if(!output.isNull("id"))
        {
            output.setId(output.get<int>("id"));
        }
    }
    output.setCustomPropertiesLoaded(true);
    return true;
}

bool CustomObjectDaoSoci::updateObject(const std::string& table, CustomObject& object)
{
    shared_ptr<soci::session> session = m_sociDbConnection->session();
    soci::statement st(*session);

    CustomObject::CustomFieldMap customFieldMap = object.customFields();

    //must remain alive during statement execution
    StatementMapping mapping;

    int fieldCount = 0;

    std::stringstream query;
    query << "UPDATE " << table << " SET ";

    for(auto it = customFieldMap.begin(); it != customFieldMap.end(); it++)
    {
        if(it->first == "id")
        {
            continue;
        }
        if(object.isNull(it->first))
        {
            continue;
        }

        if(fieldCount != 0)
        {
            query << ", ";
        }
        fieldCount++;
        std::string field = it->first;
        std::string placeholder = ":" + it->first;

        query << field << "=" << placeholder;

        statementExchange(st,object,field,mapping);
    }

    if(fieldCount == 0)
    {
        return true;
    }

    query << " WHERE id = " << object.id();
    st.alloc();
    st.prepare(query.str());
    st.define_and_bind();
    try
    {
        st.execute(true);
    }
    catch(const std::exception& e)
    {
        m_error = e.what();
        return false;
    }

    return true;
}

bool CustomObjectDaoSoci::insertObject(const std::string& table, CustomObject& object)
{
    //TODO - tratar bancos sem autoincrement no id. Postgres possui.

    shared_ptr<soci::session> session = m_sociDbConnection->session();
    soci::statement st(*session);
    long nextId = -1;
    bool autoIncrementedId = true;

    CustomObject::CustomFieldMap customFieldMap = object.customFields();

    //must remain alive until statement execution
    StatementMapping mapping;

    std::stringstream fieldsQuery;
    std::stringstream valuesQuery;

    int fieldsCount = 0;
    for(auto it = customFieldMap.begin(); it != customFieldMap.end(); it++)
    {
        if(autoIncrementedId && it->first == "id")
        {
            continue;
        }
        if(object.isNull(it->first))
        {
            continue;
        }

        if(fieldsCount != 0)
        {
            fieldsQuery << ", ";
            valuesQuery << ", ";
        }
        fieldsCount++;
        std::string field = it->first;
        fieldsQuery << field;
        std::string fieldPlaceholder = ":" + field;
        valuesQuery << fieldPlaceholder;

        statementExchange(st,object,field,mapping);
    }

    std::stringstream query;
    if(fieldsCount == 0)
    {
        query << "INSERT INTO " << table << " DEFAULT VALUES ";
    }
    else
    {
        query << "INSERT INTO " << table << "(" << fieldsQuery.str() << ") VALUES (" << valuesQuery.str() << ") ";
    }
    if(m_sociDbConnection->databaseDriver() == SociDbConnection::POSTGRESQL)
    {
        query << " RETURNING id ";
        st.exchange(soci::into(nextId));
        autoIncrementedId = false;
    }
    st.alloc();
    st.prepare(query.str());
    st.define_and_bind();
    try
    {
        st.execute(true);
    }
    catch(const std::exception& e)
    {
        m_error = std::string("") + e.what() + "\n query: " + session->get_last_query();
        cout << "erro: " << e.what() << endl;
//        cout << "query: " << session->get_last_query();
        return false;
    }

    if(autoIncrementedId)
    {
        bool insertOk = session->get_last_insert_id(table, nextId);
        if(!insertOk)
        {
            stringstream ss;
            ss << "couldn't read generated  id. " << nextId << "; " << session->get_last_query() << "; " << endl;
            m_error = ss.str();
            return false;
        }
    }
    if(nextId == -1)
    {
        stringstream ss;
        ss << "[2] couldn't read generated  id . " << nextId << "; " << session->get_last_query() << "; " << endl;
        m_error = ss.str();
        return false;
    }

    object.setId(nextId);
    object.addField("id");
    object.set<int>("id", nextId);
    return true;
}

bool CustomObjectDaoSoci::remove(const std::string& table, const std::string& filter)
{
    std::shared_ptr<soci::session> session = m_sociDbConnection->session();
    try
    {
        int count;
        *session << "SELECT count(*) FROM " << table << " WHERE " << filter, soci::into(count);
        if(count > 0)
        {
            *session << "DELETE FROM " << table << " WHERE " << filter;
        }
        else
        {
            m_error = "CustomObjectDaoSoci::remove -> object not found ";
            return false;
        }
    }
    catch(const std::exception& e)
    {
        m_error = e.what();
        return false;
    }
    return true;
}

void CustomObjectDaoSoci::statementExchange(soci::statement& st,
        CustomObject& object,
        const std::string& field,
        StatementMapping& mapping)
{
    auto fieldType = object.getFieldType(field);

    switch(fieldType)
    {
    case CustomObject::FIELD_TYPE_UNKNOWN:
    case CustomObject::FIELD_TYPE_STRING:
        mapping.strValues[field] = object.get<std::string>(field);
        st.exchange(soci::use(mapping.strValues[field], field));
        break;
    case CustomObject::FIELD_TYPE_INT:
        mapping.intValues[field] = object.get<int>(field);
        st.exchange(soci::use(mapping.intValues[field], field));
        break;
    case CustomObject::FIELD_TYPE_DOUBLE:
        mapping.doubleValues[field] = object.get<double>(field);
        st.exchange(soci::use(mapping.doubleValues[field], field));
        break;
    case CustomObject::FIELD_TYPE_DATE_TIME:
        std::cout << "SETANDO DATE_TIME: " << field << std::endl;
        mapping.tmValues[field] = object.get<std::tm>(field);
        st.exchange(soci::use(mapping.tmValues[field], field));
        break;
    case CustomObject::FIELD_TYPE_LONG:
        mapping.longValues[field] = object.get<long>(field);
        st.exchange(soci::use(mapping.longValues[field], field));
        break;
    case CustomObject::FIELD_TYPE_LONG_LONG:
        mapping.llongValues[field] = object.get<long long>(field);
        st.exchange(soci::use(mapping.llongValues[field], field));
        break;
    case CustomObject::FIELD_TYPE_UNSIGNED_LONG_LONG:
        mapping.ullongValues[field] = object.get<unsigned long long>(field);
        st.exchange(soci::use(mapping.ullongValues[field], field));
        break;
    }
}

}
