#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

enum FIELD_ID{
    IDNUMBER,
    NAME,
    FED,
    SEX,
    TIT,
    WIT,
    OTIT,
    SRTNG,
    SGM,
    SK,
    RRTNG,
    RGM,
    RK,
    BTNG,
    BGM,
    BK,
    B_DAY,
    FLAG,
    FIELD_COUNT
};

class Player{
public:
    string property[FIELD_COUNT];
};

struct FieldMask{
    int pos;
    int len;
    FieldMask(){
        pos = 0;
        len = 10;
    }
    FieldMask(int p, int l){
        pos = p;
        len = l;
    }
};

FieldMask fieldMask[FIELD_COUNT];
string fieldNames[FIELD_COUNT];

void initMask(){
    fieldMask[IDNUMBER] = FieldMask(0, 15);
    fieldMask[NAME] = FieldMask(15, 61);
    fieldMask[FED] = FieldMask(76, 4);
    fieldMask[SEX] = FieldMask(80, 4);
    fieldMask[TIT] = FieldMask(84, 5);
    fieldMask[WIT] = FieldMask(89, 5);
    fieldMask[OTIT] = FieldMask(94, 15);
    fieldMask[SRTNG] = FieldMask(109, 6);
    fieldMask[SGM] = FieldMask(115, 4);
    fieldMask[SK] = FieldMask(119, 3);
    fieldMask[RRTNG] = FieldMask(122, 6);
    fieldMask[RGM] = FieldMask(128, 4);
    fieldMask[RK] = FieldMask(132, 3);
    fieldMask[BTNG] = FieldMask(135, 6);
    fieldMask[BGM] = FieldMask(141, 4);
    fieldMask[BK] = FieldMask(145, 3);
    fieldMask[B_DAY] = FieldMask(148, 6);
    fieldMask[FLAG] = FieldMask(154, 4);

    fieldNames[IDNUMBER] = "id";
    fieldNames[NAME] = "name";
    fieldNames[FED] = "federation";
    fieldNames[SEX] = "sex";
    fieldNames[TIT] = "tittle";
    fieldNames[WIT] = "wit";
    fieldNames[OTIT] = "otit";
    fieldNames[SRTNG] = "srtng";
    fieldNames[SGM] = "sgm";
    fieldNames[SK] = "sk";
    fieldNames[RRTNG] = "rrtng";
    fieldNames[RGM] = "rgm";
    fieldNames[RK] = "rk";
    fieldNames[BTNG] = "btng";
    fieldNames[BGM] = "bgm";
    fieldNames[BK] = "bk";
    fieldNames[B_DAY] = "bday";
    fieldNames[FLAG] = "flag";
}

string trim(const string& s){
    string r = s;
    int first = 0;
    int last = 0;

    first = r.find_first_not_of(' ');
    if(first != string::npos)
    {
        r = r.substr(first);
    }
    last = r.find_last_not_of(' ');
    if(last != string::npos)
    {
        r = r.substr(0, last+1);
    }
    return r;
}

string create_table(){
    string sql;
    sql += "CREATE TABLE player(\n";
    for(int i = 0; i < FIELD_COUNT; i++){
        sql += "\t" + fieldNames[i];
        sql += i == 0 ? " SERIAL" : " VARCHAR(60)";
        sql += ", \n";
    }
    sql += "PRIMARY KEY(id) \n ";
    sql += ");\n";

    return sql;
}


Player* parseString(const string &playerString){
    Player *p = new Player;
    for(int i = 0; i < FIELD_COUNT; i++){

        string property = playerString.substr(fieldMask[i].pos, fieldMask[i].len);
        property = trim(property);
        p->property[i] = property;

    }
    return p;
}

string player2sql(const Player& p){
    string columns;
    string fields;
    for(int i=0; i < FIELD_COUNT; i++)
    {
        if( i != 0){
            columns += ", ";
            fields += ", '";
        }
        columns += fieldNames[i];
        fields += p.property[i];
        if(i != 0){
            fields += "'";
        }
    }
    string sql = "INSERT INTO player (" + columns + ") \n " +
                 "             VALUES (" + fields + ");\n";
    return sql;


}

int main(int argc, char** argv){
    ifstream input;

    ofstream output;
    output.open("players.sql");
    if(!output.good()){
        cout << "erro ao abrir players.sql";
        return 0;
    }
    //std::string playerLine;
    char playerLine[200];
    strcpy(playerLine, "teste");
    input.open ("players_list.txt");

    if(!input.good()){
        cout << "erro ao abrir players_list.txt";
        return 0;
    }

    initMask();
    output << create_table();

    while(!input.eof()){
        input.getline(playerLine, 200);

        if(strlen(playerLine) <= 100){
            cout << "linha incompleta: " << playerLine;
            continue;
        }
        Player *p = parseString(playerLine);
        output << player2sql(*p);
        //cout << "inserindo " << p->property[NAME] << "." << endl;
        delete p;
    }
    output.close();
    input.close();

    std::cout << playerLine << endl;;

}
