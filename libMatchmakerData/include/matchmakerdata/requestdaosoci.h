#ifndef REQUESTDAOSOCI_H
#define REQUESTDAOSOCI_H

#include "requestdao.h"
#include "customobjectdaosoci.h"

namespace mm
{

class RequestDaoSoci : public RequestDao, public CustomObjectDaoSoci
{
public:
    RequestDaoSoci(mm::SociDbConnection* connection);
    virtual ~RequestDaoSoci();
    bool saveRequest(Request& request) override;
    bool loadRequest(Request& request) override;
    bool removeRequest(Request& request) override;
protected:
private:
    std::string m_table;
};

};

#endif // REQUESTDAOSOCI_H
