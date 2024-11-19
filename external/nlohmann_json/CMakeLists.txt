include(FetchContent)

set(NLOHMANN_JSON_PROJECT "nlohmann_json")
set(NLOHMANN_JSON_PATH "${EXTERNAL_PATH}/nlohmann_json")
set(NLOHMANN_JSON_DOWNLOAD_DIR ${NLOHMANN_JSON_PATH}/src)

FetchContent_Declare(
    ${NLOHMANN_JSON_PROJECT}
    URL "${GITHUB_BASEURL}/nlohmann/json/releases/download/v3.11.2/json.tar.xz"
    URL_MD5 "127794b2c82c0c5693805feaa2a703e2"
)

FetchContent_MakeAvailable(${NLOHMANN_JSON_PROJECT})