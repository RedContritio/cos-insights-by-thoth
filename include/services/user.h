#ifndef USER_SERVICE_H
#define USER_SERVICE_H

#include "services/base.h"
#include "repositories/user.h"
#include <vector>

class UserService : public BaseService<UserRepository> {
public:
    UserService(UserRepository& userRepository);

    bool create_user(const std::string& username, const std::string& password);
    bool login_user(const std::string& username, const std::string& password, User& out_user);

    User get_user_by_username(const std::string& username) const;
    std::vector<User> get_all_users() const;

    User update_user(const User& user);

    bool delete_user(int userId);

    static const int USER_NOT_FOUND = -1;
    static const int USER_NOT_REGISTERED = -2;
};

#endif