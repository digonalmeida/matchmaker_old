#ifndef LOAD_CONNECTION_H
#define LOAD_CONNECTION_H

#include <memory>
#include <matchmakerdata/dbconnection.h>

using namespace std;

shared_ptr<mm::DbConnection> loadConnection();

#endif
