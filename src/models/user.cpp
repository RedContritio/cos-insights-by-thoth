#include "models/user.h"
#include <iostream>
#include <openssl/sha.h>
#include <sqlite3.h>

using std::string;

using db::db_conn_t;

User::User(int uid, const string& username, const string& pwd_hashed) : id(uid), username(username), password_hashed(pwd_hashed) {}