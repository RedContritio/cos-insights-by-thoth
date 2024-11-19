cmake_minimum_required(VERSION 3.5)
include(FetchContent)

set(JWTCPP_PROJECT "jwt-cpp")

FetchContent_Declare(
    ${JWTCPP_PROJECT}
    GIT_REPOSITORY "https://github.com/Thalhammer/jwt-cpp.git"
    GIT_TAG "v0.7.0"
)

set(JWT_BUILD_EXAMPLES OFF)

FetchContent_MakeAvailable(${JWTCPP_PROJECT})