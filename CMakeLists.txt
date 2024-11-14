cmake_minimum_required(VERSION 3.10)

set(MAIN_PROJECT "cos-insight-by-thoth")
set(MAIN_TARGET "cibt")

project(${MAIN_PROJECT})

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(EXTERNAL_PATH ${CMAKE_BINARY_DIR}/external)
add_subdirectory(external/jwt-cpp)

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
file(GLOB CONTROLLERS_SRC_FILES "src/controllers/*.cpp")
file(GLOB MODELS_SRC_FILES "src/models/*.cpp")
file(GLOB REPOSITORY_SRC_FILES "src/repositories/*.cpp")
file(GLOB SERVICES_SRC_FILES "src/services/*.cpp")
file(GLOB UTILS_SRC_FILES "src/utils/*.cpp")

set(SOURCE_FILES ${CONTROLLERS_SRC_FILES} ${MODELS_SRC_FILES} ${REPOSITORY_SRC_FILES} ${SERVICES_SRC_FILES} ${UTILS_SRC_FILES})

add_executable(${MAIN_TARGET} src/main.cpp ${SOURCE_FILES})

add_dependencies(${MAIN_TARGET} jwt-cpp)

# 链接所需的库
target_link_libraries(${MAIN_TARGET} PRIVATE PkgConfig::Pistache jwt-cpp::jwt-cpp
                        ${OpenCV_LIBS}
                        ${SQLite3_LIBRARIES})

enable_testing()