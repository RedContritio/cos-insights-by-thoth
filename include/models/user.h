#ifndef USER_H
#define USER_H

#include <string>
#include "utils/database_connection.h"

class User {
public:
    int id;
    std::string username;
    std::string password_sha256;

    User(int uid, const std::string& username, const std::string& pwd_sha256);

    bool verify(std::string pwd_input);

    static User& create(const db::db_conn_t& conn, User& user);
    static int create(const db::db_conn_t& conn, const std::string& username, const std::string& pwd_input);
    
    static bool _create_table(const db::db_conn_t& conn);
};

#endif