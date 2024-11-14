#include "services/user.h"
#include "utils/hash.h"

using std::string;
using std::vector;

UserService::UserService(UserRepository& userRepository) : BaseService<UserRepository>(userRepository) {}

bool UserService::create_user(const std::string& username, const std::string& password) {
    auto& userRepository = _repository;
    std::string pwd_hashed = calculateHash(password);

    User user(UserService::USER_NOT_REGISTERED, username, pwd_hashed);
    int id = userRepository.create_user(user);
    return id != -1;
}

bool UserService::login_user(const std::string& username, const std::string& password, User& out_user) {
    auto& userRepository = _repository;
    std::string pwd_hashed = calculateHash(password);

    int id = userRepository.get_user_id_by_name(username);
    if (id == -1) {
        return false;
    }

    if (!userRepository.get_user_by_id(id, out_user)) {
        return false;
    }

    return pwd_hashed == out_user.password_hashed;
}


User UserService::get_user_by_username(const std::string& username) const {
    auto& userRepository = _repository;
    auto id = userRepository.get_user_id_by_name(username);

    User user(UserService::USER_NOT_FOUND, "", "");
    userRepository.get_user_by_id(id, user);

    return user;
}


vector<User> UserService::get_all_users() const {
    auto& userRepository = _repository;
    return userRepository.get_all_users();
}


User UserService::update_user(const User& user) {
    auto& userRepository = _repository;
    userRepository.update_user(user);
    return user;
}


bool UserService::delete_user(int userId)
{
    auto& userRepository = _repository;
    return userRepository.delete_user(userId);
}