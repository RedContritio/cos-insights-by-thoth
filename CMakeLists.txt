cmake_minimum_required(VERSION 3.10)

set(MAIN_PROJECT "cos-insight-by-thoth")
set(MAIN_TARGET "cibt")

project(${MAIN_PROJECT})

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(GITHUB_BASEURL "https://ghp.ci/https://github.com")

# third-party libraries

set(EXTERNAL_PATH ${PROJECT_SOURCE_DIR}/external)
add_subdirectory(${EXTERNAL_PATH}/nlohmann_json)
add_subdirectory(${EXTERNAL_PATH}/jwt-cpp)

include_directories(${PROJECT_SOURCE_DIR}/include
                    ${NLOHMANN_JSON_INCLUDE_DIR}
                    ${JWTCPP_INCLUDE_DIR})

## Pistache
find_package(PkgConfig)
pkg_check_modules(Pistache REQUIRED IMPORTED_TARGET libpistache)

find_package(OpenCV REQUIRED)

# SQLite
find_package(SQLite3 REQUIRED)

# Src files
file(GLOB_RECURSE PROJECT_CPP_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")

add_executable(${MAIN_TARGET} ${PROJECT_CPP_FILES})

add_dependencies(${MAIN_TARGET} jwt-cpp)

# Linking
target_link_libraries(${MAIN_TARGET} PRIVATE PkgConfig::Pistache jwt-cpp::jwt-cpp
                        ${OpenCV_LIBS}
                        ${SQLite3_LIBRARIES})

enable_testing()