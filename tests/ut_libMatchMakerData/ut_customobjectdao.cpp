#include <gtest/gtest.h>

#include <memory>
#include "ut_customobjectdao.h"
#include <matchmakerdata/customobject.h>
#include <matchmakerdata/dbconnectionfactory.h>
#include <matchmakerdata/customobjectdao.h>
#include <matchmakerdata/dbconnection.h>
#include "loadConnection.h"
#include <ctime>
//#define CONNECTION_TYPE mm::DbConnectionFactory::CONNECTION_TYPE_SOCI_POSTGRESQL
//#define CONNECTION_HOST "localhost"
//#define CONNECTION_USER "matchmaker"
//#define CONNECTION_PASS "matchmaker"
//#define CONNECTION_DB "matchmaker"

using namespace std;

//shared_ptr<mm::DbConnection> loadConnection()
//{
//
//    shared_ptr<mm::DbConnection> con;
//    mm::DbConnectionFactory factory;
//    con = factory.makeConnection(CONNECTION_TYPE,
//                                 CONNECTION_HOST,
//                                 CONNECTION_USER,
//                                 CONNECTION_PASS,
//                                 CONNECTION_DB);
//    return con;
//}

TEST (CustomObjectDao, constructor)
{
    shared_ptr<mm::DbConnection> con = loadConnection();
    shared_ptr<mm::CustomObjectDao> customObjectDao = con->customObjectDao();
    EXPECT_FALSE(customObjectDao.get() == NULL);
}

TEST (CustomObjectDao, load_bad_filter)
{
    shared_ptr<mm::DbConnection> con = loadConnection();
    shared_ptr<mm::CustomObjectDao> customObjectDao = con->customObjectDao();
    mm::CustomObject customObject;
    bool loaded = customObjectDao->loadCustomPropertiesWithFilter("profile", "name liake 'asdfasdf'", customObject);
    EXPECT_FALSE(loaded);
    EXPECT_FALSE(customObject.customPropertiesLoaded());
}

TEST (CustomObjectDao, load)
{

    shared_ptr<mm::DbConnection> con = loadConnection();
    shared_ptr<mm::CustomObjectDao> customObjectDao = con->customObjectDao();
    mm::CustomObject customObject;
    bool loaded = customObjectDao->loadCustomPropertiesWithFilter("profile", "name like '%Rodrigo%'", customObject);
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
            EXPECT_TRUE(customObject.customPropertiesLoaded());
        }
    }
}

TEST (CustomObjectDao, insert_update_delete)
{
    shared_ptr<mm::DbConnection> con = loadConnection();
    shared_ptr<mm::CustomObjectDao> customObjectDao = con->customObjectDao();
    mm::CustomObject customObject;
    customObject.addField("name");
    customObject.addField("someInt");
    customObject.set<std::string>("name", "Rodrigo Nietiedt");
    bool saved = customObjectDao->saveCustomProperties("profile", customObject);

    EXPECT_TRUE(saved);
    if(!saved)
    {
        std::cout << "erro: " << customObjectDao->getError();
    }
    int newId = customObject.id();
    std::cout << "---------- --- ----- new Id: " << newId << endl;
    mm::CustomObject customObjectLoaded;
    bool loaded = customObjectDao->loadCustomPropertiesWithId("profile", newId, customObjectLoaded);
    EXPECT_TRUE(loaded);
    EXPECT_TRUE(customObjectLoaded.contains("id"));
    EXPECT_FALSE(customObjectLoaded.isNull("id"));
    EXPECT_TRUE(customObjectLoaded.contains("name"));
    EXPECT_FALSE(customObjectLoaded.isNull("name"));
    std::string nameLoaded = customObjectLoaded.get<std::string>("name");
    int loadedId = customObjectLoaded.get<int>("id");

    EXPECT_EQ("Rodrigo Nietiedt", nameLoaded);
    EXPECT_EQ(newId, loadedId);
    EXPECT_EQ(newId,  customObjectLoaded.id());


    customObjectLoaded.set<std::string>("name", "Rodrigo Almeida");
    bool salvou = customObjectDao->saveCustomProperties("profile", customObjectLoaded);
    EXPECT_TRUE(salvou);
    mm::CustomObject customObjectUpdated;
    loaded = customObjectDao->loadCustomPropertiesWithId("profile", newId, customObjectUpdated);

    EXPECT_TRUE(loaded);
    EXPECT_TRUE(customObjectUpdated.contains("id"));
    EXPECT_FALSE(customObjectUpdated.isNull("id"));
    EXPECT_TRUE(customObjectUpdated.contains("name"));
    EXPECT_FALSE(customObjectUpdated.isNull("name"));

    nameLoaded = customObjectUpdated.get<std::string>("name");
    loadedId = customObjectUpdated.get<int>("id");

    EXPECT_EQ("Rodrigo Almeida", nameLoaded);
    EXPECT_EQ(newId, loadedId);

    bool removed = customObjectDao->remove("profile", customObjectUpdated);
    if(!removed)
    {
        std::cout << "erro: " << customObjectDao->getError();
    }
    EXPECT_TRUE(removed);

    EXPECT_EQ(mm::CustomObject::nullId, customObjectUpdated.id());
    removed = customObjectDao->remove("profile", customObjectUpdated);
    EXPECT_FALSE(removed);
    removed = customObjectDao->remove("profile", customObjectLoaded);
    EXPECT_FALSE(removed);

    loaded = customObjectDao->loadCustomProperties("profile", customObject);
    EXPECT_FALSE(loaded);
    loaded = customObjectDao->loadCustomProperties("profile", customObjectLoaded);
    EXPECT_FALSE(loaded);

    std::cout << "novo id: " << newId << endl;
}
