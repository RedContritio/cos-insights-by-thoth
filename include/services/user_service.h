#ifndef USER_SERVICE_H
#define USER_SERVICE_H

#include "../repositories/user_repository.h"

class UserService {
public:
    UserService(UserRepository& userRepository);

    // 例如：用户注册方法
    bool registerUser(const std::string& username, const std::string& password);

    // 用户登录方法
    bool loginUser(const std::string& username, const std::string& password);

    // 查询用户信息方法
    //...

private:
    UserRepository& userRepository;
};

#endif