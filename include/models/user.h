#ifndef USER_H
#define USER_H

#include <string>
#include "utils/database_connection.h"

struct _UserAuth {
    bool is_admin;
};

class User {
public:
    int id;
    std::string username;
    std::string password_hashed;
    _UserAuth auth;

    User(int uid, const std::string& username, const std::string& pwd_hashed);

    static bool _create_table(const db::db_conn_t& conn);
};

#endif