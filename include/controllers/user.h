#ifndef USER_CONTROLLER_H
#define USER_CONTROLLER_H

#include <pistache/http.h>
#include <pistache/router.h>
#include "controllers/base.h"
#include "services/user.h"

class UserController : public BaseController<UserService> {
public:
    UserController(UserService& userService);
    void setup_routes(Pistache::Rest::Router& router);

    void get_all_users(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void get_user_by_username(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void create_user(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void update_user(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void delete_user(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
};

#endif