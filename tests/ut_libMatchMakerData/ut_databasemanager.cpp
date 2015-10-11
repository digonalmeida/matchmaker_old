#include <iostream>
#include <string>
#include <matchmakerdata/dbconnection.h>
#include <matchmakerdata/dbconnectionfactory.h>
#include <memory>
#include <gtest/gtest.h>

using namespace std;

#define CONNECTION_TYPE_POSTGRES mm::DbConnectionFactory::CONNECTION_TYPE_SOCI_POSTGRESQL
#define CONNECTION_HOST "localhost"
#define CONNECTION_USER "matchmaker"
#define CONNECTION_PASS "matchmaker"
#define CONNECTION_DB "teste"

TEST (DatabaseManager, postgresConnection) {
    mm::DbConnectionFactory factory;
    shared_ptr<mm::DbConnection> con = factory.makeConnection(CONNECTION_TYPE_POSTGRES,
                                                                                CONNECTION_HOST,
                                                                                CONNECTION_USER,
                                                                                CONNECTION_PASS,
                                                                                CONNECTION_DB);


    EXPECT_EQ(con->type(), "SOCI");
    EXPECT_TRUE(con->isConnected());

}

TEST (DatabaseManager, postgresConnectionWrongPassword) {
mm::DbConnectionFactory factory;
    EXPECT_ANY_THROW(factory.makeConnection(CONNECTION_TYPE_POSTGRES,
                                                             CONNECTION_HOST,
                                                             CONNECTION_USER,
                                                             "asdfsçewhk",
                                                             CONNECTION_DB));
}
