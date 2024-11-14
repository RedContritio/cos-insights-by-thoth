#include <sqlite3.h>
#include "repositories/user.h"

using db::db_conn_t;
using std::shared_ptr;
using std::string;
using std::vector;

UserRepository::UserRepository(db_conn_t conn) : BaseRepository(conn) {}

UserRepository::~UserRepository() {}

int UserRepository::create_user(const User& user) {
    const string username = user.username;
    const string pwd_hashed = user.password_hashed;
    auto conn = _conn;

    const string sql = "INSERT INTO users (username, password) VALUES (?,?);";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(_conn.get(), sql.c_str(), -1, &stmt, nullptr);
    if (rc!= SQLITE_OK) {
        std::cerr << "SQL 错误: " << sqlite3_errmsg(conn.get()) << std::endl;
        sqlite3_finalize(stmt);
        return -1;
    }
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, pwd_hashed.c_str(), -1, SQLITE_STATIC);
    rc = sqlite3_step(stmt);
    if (rc!= SQLITE_DONE) {
        std::cerr << "插入用户失败: " << sqlite3_errmsg(conn.get()) << std::endl;
        sqlite3_finalize(stmt);
        return -1;
    }
    
    const string sql_query_last = "SELECT last_insert_rowid();";
    rc = sqlite3_prepare_v2(conn.get(), sql_query_last.c_str(), -1, &stmt, nullptr);
    if (rc!= SQLITE_OK) {
        std::cerr << "SQL 错误: " << sqlite3_errmsg(conn.get()) << std::endl;
        sqlite3_finalize(stmt);
        return -1;
    }
    rc = sqlite3_step(stmt);
    int id = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    return id;
}

int UserRepository::get_user_id_by_name(const std::string username) const {
    auto conn = _conn;
    const string sql = "SELECT id FROM users WHERE username = ?;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(conn.get(), sql.c_str(), -1, &stmt, nullptr);
    if (rc!= SQLITE_OK) {
        std::cerr << "SQL 错误: " << sqlite3_errmsg(conn.get()) << std::endl;
        sqlite3_finalize(stmt);
        return -1;
    }
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    rc = sqlite3_step(stmt);
    if (rc!= SQLITE_ROW) {
        std::cerr << "用户不存在: " << sqlite3_errmsg(conn.get()) << std::endl;
        sqlite3_finalize(stmt);
        return -1;
    }
    int id = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    return id;
}


bool UserRepository::get_user_by_id(int userId, User& out_user) const {
    auto conn = _conn;
    const string sql = "SELECT * FROM users WHERE id = ?;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(conn.get(), sql.c_str(), -1, &stmt, nullptr);
    if (rc!= SQLITE_OK) {
        std::cerr << "SQL 错误: " << sqlite3_errmsg(conn.get()) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }
    sqlite3_bind_int(stmt, 1, userId);
    rc = sqlite3_step(stmt);
    if (rc!= SQLITE_ROW) {
        std::cerr << "用户不存在: " << sqlite3_errmsg(conn.get()) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    const int id = sqlite3_column_int(stmt, 0);
    const string username = string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
    const string password_hashed = string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
    
    sqlite3_finalize(stmt);

    out_user = User(id, username, password_hashed);
    return true;
}


vector<User> UserRepository::get_all_users() const {
    auto conn = _conn;
    const string sql = "SELECT * FROM users;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(conn.get(), sql.c_str(), -1, &stmt, nullptr);
    if (rc!= SQLITE_OK) {
        std::cerr << "SQL 错误: " << sqlite3_errmsg(conn.get()) << std::endl;
        sqlite3_finalize(stmt);
        return {};
    }
    vector<User> users;
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        const int id = sqlite3_column_int(stmt, 0);
        const string username = string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        const string password_hashed = string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        users.push_back(User(id, username, password_hashed));
    }
    sqlite3_finalize(stmt);
    return users;
}


bool UserRepository::update_user(const User &user)
{
    throw std::runtime_error("Not implemented");
    return false;
}

bool UserRepository::delete_user(int userId)
{
    throw std::runtime_error("Not implemented");
    return false;
}

bool UserRepository::_create_table() {
    auto conn = _conn;
    
    const char* sql = "CREATE TABLE IF NOT EXISTS users ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                      "username TEXT NOT NULL,"
                      "password TEXT NOT NULL);";
    char* errMsg;
    int rc = sqlite3_exec(conn.get(), sql, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL 错误: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}