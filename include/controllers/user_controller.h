#ifndef USER_CONTROLLER_H
#define USER_CONTROLLER_H

#include <pistache/http.h>
#include <pistache/router.h>
#include "../services/user_service.h"

class UserController {
public:
    UserController(UserService& userService);

    void setupRoutes(Pistache::Rest::Router& router);

private:
    UserService& userService;
};

#endif