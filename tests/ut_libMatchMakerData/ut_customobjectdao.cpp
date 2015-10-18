#include <gtest/gtest.h>

#include <memory>
#include "ut_customobjectdao.h"
#include <matchmakerdata/customobject.h>
#include <matchmakerdata/dbconnectionfactory.h>
#include <matchmakerdata/customobjectdao.h>
#include <matchmakerdata/dbconnection.h>

#define CONNECTION_TYPE_POSTGRES mm::DbConnectionFactory::CONNECTION_TYPE_SOCI_POSTGRESQL
#define CONNECTION_HOST "localhost"
#define CONNECTION_USER "matchmaker"
#define CONNECTION_PASS "matchmaker"
#define CONNECTION_DB "matchmaker"

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
    shared_ptr<mm::CustomObjectDao> customObjectDao = con->customObjectDao();
    EXPECT_FALSE(customObjectDao.get() == NULL);
}

TEST (CustomObjectDao, load_bad_filter){
    shared_ptr<mm::DbConnection> con = loadConnection();
    shared_ptr<mm::CustomObjectDao> customObjectDao = con->customObjectDao();
    mm::CustomObject customObject;
    bool loaded = customObjectDao->load("profile", "name liake 'asdfasdf'", &customObject);
    EXPECT_FALSE(loaded);
}

TEST (CustomObjectDao, load) {

    shared_ptr<mm::DbConnection> con = loadConnection();
    shared_ptr<mm::CustomObjectDao> customObjectDao = con->customObjectDao();
    mm::CustomObject customObject;
    bool loaded = customObjectDao->load("profile", "name like '%Rodrigo%'", &customObject);
    EXPECT_TRUE(loaded);
    if(loaded)
    {
        bool contains = customObject.contains("name");
        bool isNull = customObject.isNull("name");

        EXPECT_TRUE(contains);
        EXPECT_FALSE(isNull);
        if(contains && !isNull)
        {
            std::string name = customObject.get<std::string>("name");
            int nNamePos = name.find("Rodrigo");
            EXPECT_TRUE(nNamePos != string::npos);
            std::cout << "[        ] " << "name: " << name << endl;
        }
    }
}
