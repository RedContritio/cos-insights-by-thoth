#include "models/user.h"
#include <iostream>
#include <openssl/sha.h>
#include <sqlite3.h>

using std::string;

using db::db_conn_t;

string calculateHash(const string& text);

User::User(int uid, const string& username, const string& pwd_sha256) : id(uid), username(username), password_sha256(password_sha256) {}

bool User::verify(string pwd_input) {
    
}

User& User::create(const db::db_conn_t& conn, User& user) {
    const string& username = user.username;
    const string& pwd_sha256 = user.password_sha256;
    int id = User::create(conn, username, pwd_sha256);
    user.id = id;
    return user;
}

int User::create(const db_conn_t& conn, const string& username, const string& pwd_sha256) {
    std::string sql = "INSERT INTO users (username, password) VALUES (?,?);";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(conn.get(), sql.c_str(), -1, &stmt, nullptr);
    if (rc!= SQLITE_OK) {
        std::cerr << "SQL 错误: " << sqlite3_errmsg(conn.get()) << std::endl;
        sqlite3_finalize(stmt);
        return -1;
    }
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, pwd_sha256.c_str(), -1, SQLITE_STATIC);
    rc = sqlite3_step(stmt);
    if (rc!= SQLITE_DONE) {
        std::cerr << "插入用户失败: " << sqlite3_errmsg(conn.get()) << std::endl;
        sqlite3_finalize(stmt);
        return -1;
    }
    
    sql = "SELECT last_insert_rowid();";
    rc = sqlite3_prepare_v2(conn.get(), sql.c_str(), -1, &stmt, nullptr);
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


bool User::_create_table(const db_conn_t& conn) {
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

std::string calculateHash(const string& text) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, text.c_str(), text.length());
    SHA256_Final(hash, &sha256);

    char buf[2 * SHA256_DIGEST_LENGTH + 1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(buf + 2 * i, "%02x", hash[i]);
    }
    buf[2 * SHA256_DIGEST_LENGTH] = '\0';

    return std::string(buf);
}
