cmake_minimum_required(VERSION 3.10)

project(cos-insights-by-thoth)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(${CMAKE_SOURCE_DIR}/third_party/rapidjson/include)
include_directories(${PROJECT_SOURCE_DIR}/include)

include(FetchContent)

# third-party libraries

## Pistache
find_package(PkgConfig)
pkg_check_modules(Pistache REQUIRED IMPORTED_TARGET libpistache)

find_package(OpenCV REQUIRED)

# SQLite
find_package(SQLite3 REQUIRED)

# 添加可执行文件的源文件
add_executable(${PROJECT_NAME} src/main.cpp)

# 链接所需的库
target_link_libraries(${PROJECT_NAME} PkgConfig::Pistache
                        ${OpenCV_LIBS}
                        ${SQLite3_LIBRARIES})

enable_testing()