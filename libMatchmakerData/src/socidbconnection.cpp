#include "socidbconnection.h"
#include <iostream>
SOCIDBConnection::SOCIDBConnection()
{
    //ctor
    m_type = "SOCI";
    m_isConnected = true;
}

SOCIDBConnection::~SOCIDBConnection()
{
    //dtor
}
bool SOCIDBConnection::connect(std::string type, std::string host, std::string user, std::string pass, std::string database)
{
    m_isConnected = true;
    m_session = std::shared_ptr<soci::session>(new soci::session());
    if(type == "postgresql"){
        std::string connectionString = "host='" + host + "' user='" + user + "' password='" + pass + "' dbname='" + database + "'";
        m_session->open(soci::postgresql, connectionString);
        m_isConnected = true;
        return true;
    }
    else{
        throw std::string("teste");
        return false;
    }
}
