#include <iostream>
#include <pistache/endpoint.h>
#include <pistache/router.h>
#include "controllers/user_controller.h"
#include "controllers/project_controller.h"
#include "controllers/photo_controller.h"
#include "controllers/project_role_controller.h"
#include "services/user_service.h"
#include "services/project_service.h"
#include "services/photo_service.h"
#include "services/project_role_service.h"

using namespace Pistache;

using Pistache::Rest::Router;

int main(int argc, char* argv[]) {
    Port port(9080);
    int thr = 2;

    Address addr(Ipv4::any(), port);

    std::cout << "C++ Pistache server listening on port " << port << std::endl;

    auto opts = Http::Endpoint::options().threads(thr);
    Http::Endpoint server(addr);
    server.init(opts);

    Router router;

    UserRepository userRepository;

    // 创建服务实例
    UserService userService(userRepository);
    ProjectService projectService;
    PhotoService photoService;
    ProjectRoleService projectRoleService;

    // 设置用户相关路由
    UserController userController(userService);
    userController.setupRoutes(router);

    // 设置项目相关路由
    ProjectController projectController(projectService);
    projectController.setupRoutes(router);

    // 设置照片相关路由
    PhotoController photoController(photoService);
    photoController.setupRoutes(router);

    // 设置项目角色相关路由
    ProjectRoleController projectRoleController(projectRoleService);
    projectRoleController.setupRoutes(router);

    server.setHandler(router.handler());

    server.start();

    std::cout << "Server started." << std::endl;

    // 等待服务器停止
    server.waitForShutdown();

    return 0;
}