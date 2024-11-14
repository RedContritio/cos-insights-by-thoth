cmake_minimum_required(VERSION 3.5)
include(FetchContent)

set(JWTCPP_PROJECT "jwt-cpp")
set(JWTCPP_PATH "${EXTERNAL_PATH}/jwt-cpp")
set(JWTCPP_DOWNLOAD_DIR ${JWTCPP_PATH}/src)

message(STATUS "EXTERNAL_PROJECT_DIR: ${EXTERNAL_PROJECT_DIR}")

FetchContent_Declare(
    ${JWTCPP_PROJECT}
    GIT_REPOSITORY "https://github.com/Thalhammer/jwt-cpp.git"
    GIT_TAG "v0.7.0"
)

FetchContent_MakeAvailable(${JWTCPP_PROJECT})