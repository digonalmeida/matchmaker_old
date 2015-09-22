#include <gtest/gtest.h>

#include <memory>
#include "ut_customobjectdao.h"
#include <matchmakerdata/customobject.h>
#include <matchmakerdata/dbconnectionfactory.h>
#include <matchmakerdata/customobjectdao.h>
#include <matchmakerdata/dbconnection.h>

#define CONNECTION_TYPE_POSTGRES "postgres"
#define CONNECTION_HOST "localhost"
#define CONNECTION_USER "matchmaker"
#define CONNECTION_PASS "matchmaker"
#define CONNECTION_DB "teste"

using namespace std;

shared_ptr<mm::DbConnection> loadConnection(){

    shared_ptr<mm::DbConnection> con;
    mm::DbConnectionFactory factory;
    con = factory.makeConnection(CONNECTION_TYPE_POSTGRES,
                                CONNECTION_HOST,
                                CONNECTION_USER,
                                CONNECTION_PASS,
                                CONNECTION_DB);
    return con;
}

TEST (CustomObjectDao, constructor) {
    shared_ptr<mm::DbConnection> con = loadConnection();
    shared_ptr<mm::CustomObjectDao> coDao = con->customObjectDao();
}

TEST (CustomObjectDao, load) {

}
