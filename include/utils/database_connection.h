#ifndef DATABASE_CONNECTION_SINGLETON_H
#define DATABASE_CONNECTION_SINGLETON_H

#include <sqlite3.h>
#include <iostream>
#include <memory>

class DatabaseConnectionSingleton {
public:
    static DatabaseConnectionSingleton& getInstance();

    std::shared_ptr<sqlite3> getDatabaseConnection();

private:
    DatabaseConnectionSingleton();
    ~DatabaseConnectionSingleton();

    std::shared_ptr<sqlite3> db;
};

#endif