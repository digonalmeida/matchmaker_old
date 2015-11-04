#ifndef DBCONNECTIONSETTINGS_H
#define DBCONNECTIONSETTINGS_H
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>


class DbConnectionSettings
{
    public:
        DbConnectionSettings(){
            type = "";
            host = "";
            user = "";
            pass = "";
            database = "";
        }
        DbConnectionSettings(std::string filename)
        {
            load(filename);
        }

        std::string type;
        std::string host;
        std::string user;
        std::string pass;
        std::string database;

        void load(std::string filename){
        m_filename = filename;
        using boost::property_tree::ptree;
        ptree pt;
        read_ini(filename, pt);
        type = pt.get<std::string>("database.type", "");
        host = pt.get<std::string>("database.host", "");
        user = pt.get<std::string>("database.user", "");
        pass = pt.get<std::string>("database.pass", "");
        database = pt.get<std::string>("database.database","");
    }
    void save(){
        save(m_filename);
    }
    void save(std::string filename){
        using boost::property_tree::ptree;
        ptree pt;

        pt.put("database.type", type);
        pt.put("database.host", host);
        pt.put("database.user", user);
        pt.put("database.pass", pass);
        pt.put("database.database", database);
        write_ini(filename, pt);
    }

    protected:
    private:
    std::string m_filename;
};

std::ostream& operator<<(ostream& o, const DbConnectionSettings& s){
        o << "type: " << s.type
          << ", host: " << s.host
          << ", user: " << s.user
          << ", pass: " << s.pass
          << ", database: " << s.database;
}

#endif // DBCONNECTIONSETTINGS_H
