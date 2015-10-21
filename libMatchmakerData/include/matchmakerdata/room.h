#ifndef ROOM_H
#define ROOM_H

#include <string>
#include "customobject.h"

namespace mm
{
class Room : public CustomObject
{
public:
    static int nullId;
    static std::string nullAddress;
    Room();
    int id() const;
    std::string serverAddress() const ;
    bool available() const;

    void setId(int id);
    void setServerAddress(const std::string &serverAddress);
    void setAvailable(bool available);
private:
    int m_id;
    std::string m_serverAddress;
    bool m_available;
};
};

#endif
