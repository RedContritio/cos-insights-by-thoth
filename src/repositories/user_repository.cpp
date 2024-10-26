#include <sqlite3.h>
#include "repositories/user_repository.h"

UserRepository::UserRepository(std::shared_ptr<sqlite3> dbConnection) : BaseRepository(dbConnection) {}

UserRepository::~UserRepository() {}

bool UserRepository::saveUser(const User& user) {
    sqlite3_stmt* stmt;
    std::string sql = "INSERT INTO users (username, password) VALUES (?,?)";
    int rc = sqlite3_prepare_v2(db.get(), sql.c_str(), -1, &stmt, nullptr);
    if (rc!= SQLITE_OK) {
        return false;
    }
    sqlite3_bind_text(stmt, 1, user.username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, user.password.c_str(), -1, SQLITE_STATIC);
    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return rc == SQLITE_DONE;
}

User UserRepository::getUserByUsername(const std::string& username) {
    sqlite3_stmt* stmt;
    User user;
    std::string sql = "SELECT id, username, password FROM users WHERE username =?";
    int rc = sqlite3_prepare_v2(db.get(), sql.c_str(), -1, &stmt, nullptr);
    if (rc!= SQLITE_OK) {
        return user;
    }
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        user.id = sqlite3_column_int(stmt, 0);
        user.username = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        user.password = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
    }
    sqlite3_finalize(stmt);
    return user;
}

User UserRepository::getUserById(int userId) {
    sqlite3_stmt* stmt;
    User user;
    std::string sql = "SELECT id, username, password FROM users WHERE id =?";
    int rc = sqlite3_prepare_v2(db.get(), sql.c_str(), -1, &stmt, nullptr);
    if (rc!= SQLITE_OK) {
        return user;
    }
    sqlite3_bind_int(stmt, 1, userId);
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        user.id = sqlite3_column_int(stmt, 0);
        user.username = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        user.password = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
    }
    sqlite3_finalize(stmt);
    return user;
}