#ifndef USER_REPOSITORY_H
#define USER_REPOSITORY_H

#include "../models/user.h"
#include "utils/database_connection.h"
#include "base.h"
#include <vector>

class UserRepository : public BaseRepository {
public:
    UserRepository(db::db_conn_t db_conn);
    ~UserRepository();

    int create_user(const User& user);

    int get_user_id_by_name(const std::string username) const;
    bool get_user_by_id(int userId, User& out_user) const;
    std::vector<User> get_all_users() const;

    bool update_user(const User& user);

    bool delete_user(int userId);
private:
    bool _create_table();
};

#endif