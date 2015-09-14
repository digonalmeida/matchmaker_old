#include <iostream>
#include <string>
#include <matchmakerdata/dbconnection.h>
#include <memory>
#include <gtest/gtest.h>

using namespace std;

#define CONNECTION_TYPE_POSTGRES "postgres"
#define CONNECTION_HOST "localhost"
#define CONNECTION_USER "matchmaker"
#define CONNECTION_PASS "matchmaker"
#define CONNECTION_DB "teste"

TEST (DatabaseManager, postgresConnection) {

    shared_ptr<mm::DBConnection> con = mm::DBConnectionFactory::makeConnection(CONNECTION_TYPE_POSTGRES,
                                                                                CONNECTION_HOST,
                                                                                CONNECTION_USER,
                                                                                CONNECTION_PASS,
                                                                                CONNECTION_DB);
    EXPECT_TRUE(con.isConnected());
}

TEST (DatabaseManager, postgresConnectionWrongPassword) {
    EXPECT_ANY_THROW(mm::DBConnectionFactory::makeConnection(CONNECTION_TYPE_POSTGRES,
                                                             CONNECTION_HOST,
                                                             CONNECTION_USER,
                                                             "asdfsçewhk",
                                                             CONNECTION_DB));
}
