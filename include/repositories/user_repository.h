#ifndef USER_REPOSITORY_H
#define USER_REPOSITORY_H

#include "../models/user.h"
#include "utils/database_connection.h"
#include "base.h"

class UserRepository : public BaseRepository {
public:
    UserRepository(db::db_conn_t db_conn);
    ~UserRepository();

    bool saveUser(const User& user);
    User getUserByUsername(const std::string& username);
    User getUserById(int userId);
};

#endif