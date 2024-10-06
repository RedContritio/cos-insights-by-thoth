cmake_minimum_required(VERSION 3.10)

project(cos-insights-by-thoth)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")

include_directories(${CMAKE_SOURCE_DIR}/third_party/rapidjson/include)

include(FetchContent)

# third-party libraries

## Pistache
find_package(PkgConfig)
pkg_check_modules(Pistache REQUIRED IMPORTED_TARGET libpistache)

find_package(OpenCV REQUIRED)

## MySQL
set(MYSQL_CONCPP_INCLUDE_DIR /usr/include/cppconn /usr/include)
set(MYSQL_CONCPP_LIBRARY_DIR /usr/lib/x86_64-linux-gnu)
set(MYSQL_CONCPP_LIBS ${MYSQL_CONCPP_LIBRARY_DIR}/libmysqlcppconn.so)

include_directories(${MYSQL_CONCPP_INCLUDE_DIR})


# 添加可执行文件的源文件
add_executable(${PROJECT_NAME} src/main.cpp)

# 链接所需的库
target_link_libraries(${PROJECT_NAME} PkgConfig::Pistache
                        ${OpenCV_LIBS}
                        ${MYSQL_CONCPP_LIBS})

enable_testing()