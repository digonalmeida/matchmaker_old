#ifndef REQUESTDAO_H
#define REQUESTDAO_H

#include "customobjectdao.h"
#include "request.h"

namespace mm
{
class RequestDao : public virtual CustomObjectDao
{
public:
    RequestDao();
    virtual ~RequestDao();
    virtual bool saveRequest(Request& request) = 0;
    virtual bool loadRequest(Request& request) = 0;
    virtual bool removeRequest(Request& request) = 0;
protected:
private:
};
}

#endif // REQUESTDAO_H
