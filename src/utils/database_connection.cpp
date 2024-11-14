#include <filesystem>
#include "utils/database_connection.h"

using std::shared_ptr;
using std::string;

namespace db {

db_conn_t open() {
    const char* baseDirEnv = std::getenv("CIT_DATABASE_BASEDIR");
    std::string dbPath;
    if (baseDirEnv) {
        dbPath = std::string(baseDirEnv) + "/cit_data.db";
    } else {
        // 获取可执行文件所在目录
        std::filesystem::path exePath = std::filesystem::canonical("/proc/self/exe");
        std::filesystem::path parentDir = exePath.parent_path();
        dbPath = parentDir.string() + "/cit_data.db";
    }
    
    return open(dbPath);
}


db_conn_t open(string db_path) {
    db_conn_t conn;
    sqlite3* rawDb;
    int rc = sqlite3_open(db_path.c_str(), &rawDb);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(rawDb) << std::endl;
        conn.reset();
    } else {
        std::cout << "Opened database successfully" << std::endl;
        conn = std::shared_ptr<sqlite3>(rawDb, sqlite3_close);
    }
    return conn;
}

}