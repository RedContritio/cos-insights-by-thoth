include(FetchContent)

set(JWTCPP_PROJECT "jwt-cpp")
set(JWTCPP_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(JWTCPP_SOURCE_DIR "${JWTCPP_DIR}/src")

FetchContent_Declare(
    ${JWTCPP_PROJECT}
    GIT_REPOSITORY "${GITHUB_BASEURL}/Thalhammer/jwt-cpp.git"
    GIT_TAG "v0.7.0"
    SOURCE_DIR "${JWTCPP_SOURCE_DIR}"
)

set(JWT_BUILD_EXAMPLES OFF)

FetchContent_MakeAvailable(${JWTCPP_PROJECT})

set(JWTCPP_INCLUDE_DIR "${JWTCPP_SOURCE_DIR}/include" PARENT_SCOPE)
