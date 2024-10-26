#ifndef USER_REPOSITORY_H
#define USER_REPOSITORY_H

#include "../models/user.h"
#include "base.h"

class UserRepository : public BaseRepository {
public:
    UserRepository(std::shared_ptr<sqlite3> dbConnection);
    ~UserRepository();

    bool saveUser(const User& user);
    User getUserByUsername(const std::string& username);
    User getUserById(int userId);
};

#endif