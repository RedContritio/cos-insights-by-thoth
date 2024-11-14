#include <iostream>
#include <pistache/endpoint.h>
#include <pistache/router.h>
#include "controllers/user.h"
#include "controllers/project_controller.h"
#include "controllers/photo_controller.h"
#include "controllers/project_role_controller.h"
#include "services/user.h"
#include "services/project_service.h"
#include "services/photo_service.h"
#include "services/project_role_service.h"
#include "utils/database_connection.h"

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

    auto db_conn = db::open();

    UserRepository userRepository(db_conn);

    // 创建服务实例
    UserService userService(userRepository);
    // ProjectService projectService;
    // PhotoService photoService;
    // ProjectRoleService projectRoleService;

    // 设置用户相关路由
    UserController userController(userService);
    userController.setup_routes(router);

    // 设置项目相关路由
    // ProjectController projectController(projectService);
    // projectController.setup_routes(router);

    // 设置照片相关路由
    // PhotoController photoController(photoService);
    // photoController.setup_routes(router);

    // 设置项目角色相关路由
    // ProjectRoleController projectRoleController(projectRoleService);
    // projectRoleController.setup_routes(router);

    server.setHandler(router.handler());

    server.serve();

    std::cout << "Server started." << std::endl;

    return 0;
}