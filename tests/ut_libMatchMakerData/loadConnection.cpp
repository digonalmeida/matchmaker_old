#include "loadConnection.h"
#include <matchmakerdata/dbconnectionfactory.h>

shared_ptr<mm::DbConnection> loadConnection()
{

    shared_ptr<mm::DbConnection> con;
    mm::DbConnectionFactory factory;
    con = factory.makeConnection("matchmaker.ini");
    return con;
}
