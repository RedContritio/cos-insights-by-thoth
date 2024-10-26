#ifndef USER_H
#define USER_H

#include <string>

class User {
public:
    int id;
    std::string username;
    std::string password;

    User();
    User(int userId, const std::string& userName, const std::string& passWord);
};

#endif