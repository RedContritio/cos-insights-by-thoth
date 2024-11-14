#include "controllers/base.h"
#include "controllers/user.h"
#include "models/user.h"

#include <pistache/http.h>
#include <pistache/router.h>

#include <iostream>


std::string serializeUsersToJSON(const std::vector<User>& users);
std::string serializeUserToJSON(const User& user);
User parseUserFromRequest(const Pistache::Rest::Request& request);


UserController::UserController(UserService& userService) : BaseController(userService) {}

void UserController::setup_routes(Pistache::Rest::Router& router) {
    router.get("/users", Pistache::Rest::Routes::bind(&UserController::get_all_users, this));

    router.get("/users/:username", Pistache::Rest::Routes::bind(&UserController::get_user_by_username, this));

    router.post("/users", Pistache::Rest::Routes::bind(&UserController::create_user, this));

    router.put("/users/:id", Pistache::Rest::Routes::bind(&UserController::update_user, this));

    router.del("/users/:id", Pistache::Rest::Routes::bind(&UserController::delete_user, this));
}

// 处理获取所有用户的请求的函数
void UserController::get_all_users(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    try {
        auto userService = _service;

        std::vector<User> users = userService.get_all_users();

        // 将用户信息转换为JSON格式（这里假设已经有相应的JSON序列化函数）
        std::string jsonUsers = serializeUsersToJSON(users);

        // 设置响应状态码为200，并发送JSON数据
        response.send(Pistache::Http::Code::Ok, jsonUsers);
    } catch (const std::exception& e) {
        // 如果出现异常，设置响应状态码为500，并发送错误信息
        response.send(Pistache::Http::Code::Internal_Server_Error, "Error retrieving all users: " + std::string(e.what()));
    }
}

// 处理根据用户名获取用户的请求的函数
void UserController::get_user_by_username(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    try {
        auto userService = _service;

        // 从请求路径参数中获取用户名
        std::string username = request.param(":username").as<std::string>();

        // 调用UserService根据用户名获取用户
        User user = userService.get_user_by_username(username);

        // 将用户信息转换为JSON格式
        std::string jsonUser = serializeUserToJSON(user);

        // 设置响应状态码为200，并发送JSON数据
        response.send(Pistache::Http::Code::Ok, jsonUser);
    } catch (const std::exception& e) {
        // 如果出现异常，设置响应状态码为500，并发送错误信息
        response.send(Pistache::Http::Code::Internal_Server_Error, "Error retrieving user by username: " + std::string(e.what()));
    }
}

// 处理创建新用户的请求的函数
void UserController::create_user(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    try {
        auto userService = _service;

        // 从请求体中获取新用户的信息（这里假设已经有相应的解析函数）
        User newUser = parseUserFromRequest(request);
        auto username = newUser.username;
        auto password = newUser.password_hashed;

        // 调用UserService创建新用户
        userService.create_user(username, password);

        // 设置响应状态码为200，并发送成功创建的消息
        response.send(Pistache::Http::Code::Ok, "User created successfully");
    } catch (const std::exception& e) {
        // 如果出现异常，设置响应状态码为500，并发送错误信息
        response.send(Pistache::Http::Code::Internal_Server_Error, "Error creating user: " + std::string(e.what()));
    }
}

// 处理更新用户信息的请求的函数
void UserController::update_user(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    try {
        auto userService = _service;

        // 从请求路径参数中获取用户ID
        int id = request.param(":id").as<int>();

        // 从请求体中获取更新后的用户信息（这里假设已经有相应的解析函数）
        User updatedUser = parseUserFromRequest(request);

        // 设置更新后的用户ID
        updatedUser.id = id;

        // 调用UserService更新用户信息
        userService.update_user(updatedUser);

        // 设置响应状态码为200，并发送成功更新的消息
        response.send(Pistache::Http::Code::Ok, "User updated successfully");
    } catch (const std::exception& e) {
        // 如果出现异常，设置响应状态码为500，并发送错误信息
        response.send(Pistache::Http::Code::Internal_Server_Error, "Error updating user: " + std::string(e.what()));
    }
}

// 处理删除用户的请求的函数
void UserController::delete_user(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    try {
        auto userService = _service;

        // 从请求路径参数中获取用户ID
        int id = request.param(":id").as<int>();

        // 调用UserService删除用户
        userService.delete_user(id);

        // 设置响应状态码为200，并发送成功删除的消息
        response.send(Pistache::Http::Code::Ok, "User deleted successfully");
    } catch (const std::exception& e) {
        // 如果出现异常，设置响应状态码为500，并发送错误信息
        response.send(Pistache::Http::Code::Internal_Server_Error, "Error deleting user: " + std::string(e.what()));
    }
}

// 假设的将用户信息转换为JSON格式的函数
std::string serializeUsersToJSON(const std::vector<User>& users) {
    // 这里可以使用任何JSON序列化库来实现，比如nlohmann/json等
    // 以下是一个简单的示例，实际应用中需要更完善的实现
    std::string json = "[";
    for (size_t i = 0; i < users.size(); ++i) {
        if (i > 0) {
            json += ",";
        }
        json += "{\"id\":\"" + std::to_string(users[i].id) + "\",\"username\":\"" + users[i].username + "\",\"password\":\"" + users[i].password_hashed + "\"}";
    }
    json += "]";
    return json;
}

// 假设的将单个用户信息转换为JSON格式的函数
std::string serializeUserToJSON(const User& user) {
    // 同样可以使用JSON序列化库来实现，以下是简单示例
    return "{\"id\":\"" + std::to_string(user.id) + "\",\"username\":\"" + user.username + "\",\"password\":\"" + user.password_hashed + "\"}";
}


User parseUserFromRequest(const Pistache::Rest::Request& request) {
    // 这里可以使用任何请求体解析库来实现，比如Pistache自带的解析功能或者其他第三方库
    // 以下是一个简单的示例，实际应用中需要更完善的实现
    auto body = request.body();
    
    User user(0, "", "");
    // user.username = request.body()("username");
    // user.password_hashed = request.body()("password");
    throw std::runtime_error("Not implemented");
    return user;
}