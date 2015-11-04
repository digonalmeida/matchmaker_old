#include <iostream>
#include <string>
#include <matchmakerdata/dbconnection.h>
#include <matchmakerdata/dbconnectionfactory.h>
#include <memory>
#include <gtest/gtest.h>
#include "loadConnection.h"

using namespace std;

#define CONNECTION_TYPE_POSTGRES mm::DbConnectionFactory::CONNECTION_TYPE_SOCI_POSTGRESQL
#define CONNECTION_HOST "localhost"
#define CONNECTION_USER "matchmaker"
#define CONNECTION_PASS "matchmaker"
#define CONNECTION_DB "matchmaker"

TEST (DatabaseManager, postgresConnection)
{
    mm::DbConnectionFactory factory;
    shared_ptr<mm::DbConnection> con = factory.makeConnection(CONNECTION_TYPE_POSTGRES,
                                       CONNECTION_HOST,
                                       CONNECTION_USER,
                                       CONNECTION_PASS,
                                       CONNECTION_DB);


    EXPECT_EQ(con->type(), "SOCI");
    EXPECT_TRUE(con->isConnected());

}

TEST (DatabaseManager, postgresConnectionWrongPassword)
{
    mm::DbConnectionFactory factory;
    EXPECT_ANY_THROW(factory.makeConnection(CONNECTION_TYPE_POSTGRES,
                                            CONNECTION_HOST,
                                            CONNECTION_USER,
                                            "asdfsçewhk",
                                            CONNECTION_DB));
}

TEST(DatabaseManager, CustomObjectDao)
{
    auto con = loadConnection();
}

TEST(DatabaseManager, MatchDao)
{
    auto con = loadConnection();

    shared_ptr<mm::MatchDao> matchDao;
    matchDao = con->matchDao();
    EXPECT_FALSE(matchDao.get() == 0);
}

TEST(DatabaseManager, profileDao)
{
    auto con = loadConnection();

    shared_ptr<mm::ProfileDao> profileDao;
    profileDao = con->profileDao();
    EXPECT_FALSE(profileDao.get() == 0);
}

TEST(DatabaseManager, requestDao)
{
    auto con = loadConnection();
    shared_ptr<mm::RequestDao> requestDao;
    requestDao = con->requestDao();
    EXPECT_FALSE(requestDao.get() == 0);
}

TEST(DatabaseManager, roomDao)
{
    auto con = loadConnection();
    shared_ptr<mm::RoomDao> roomDao;
    roomDao = con->roomDao();
    EXPECT_FALSE(roomDao.get() == 0);
}
