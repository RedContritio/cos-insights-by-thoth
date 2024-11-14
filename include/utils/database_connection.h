#ifndef DATABASE_CONNECTION_SINGLETON_H
#define DATABASE_CONNECTION_SINGLETON_H

#include <sqlite3.h>
#include <iostream>
#include <memory>

namespace db {

using db_conn_t = std::shared_ptr<sqlite3>;

db_conn_t open();
db_conn_t open(std::string db_path);

}




class DatabaseConnectionSingleton {
public:
    static DatabaseConnectionSingleton& getInstance();

    std::shared_ptr<sqlite3> getConnection();
private:
    DatabaseConnectionSingleton();
    ~DatabaseConnectionSingleton();

    std::shared_ptr<sqlite3> db;
};

#endif