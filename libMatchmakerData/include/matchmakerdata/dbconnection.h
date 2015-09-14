#ifndef DBCONNECTION_H
#define DBCONNECTION_H
#include <string>

namespace mm{

class DBConnection
{
    public:
        DBConnection() {}
        virtual ~DBConnection() {}
        virtual bool isConnected() { return m_isConnected; }
        std::string type() const { return m_type; }
    protected:
        bool m_isConnected;
        std::string m_type;
    private:

};

};

#endif // DBCONNECTION_H
