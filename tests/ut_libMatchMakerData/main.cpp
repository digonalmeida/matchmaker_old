#include <iostream>
#include <gtest/gtest.h>
#include <soci/session.h>

#include <soci/session.h>
#include <soci/postgresql/soci-postgresql.h>
#include <soci.h>
#include <boost-optional.h>
#include <vector>

using namespace std;
void teste();

int main(int argc, char** argv){
    testing::InitGoogleTest(&argc, argv);
    //teste();
    return  RUN_ALL_TESTS();
}
/*

void teste(){
    soci::session session;

    try{
        session.open(soci::postgresql, "host='localhost' user='matchmaker' password='matchmaker' dbname='teste'");
        std::vector< boost::optional<string> > ids (100);
        session << "select name from teste", soci::into< std::vector< boost::optional<string> > >(ids);

        for(unsigned int i = 0; i < ids.size(); i++){
            boost::optional<string> id = ids[i];
            if(id){
                cout << "name: " << *id << endl;
            }
            else{
                cout << "name: " << "null" << endl;
            }
        }

    }
    catch(soci::soci_error error){
        std::cout << "Erro ao conectar ao banco: " << error.what() << std::endl;
    }
*/
