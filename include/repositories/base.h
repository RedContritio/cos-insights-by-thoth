#ifndef BASE_REPOSITORY_H
#define BASE_REPOSITORY_H

#include <memory>
#include <vector>
#include <functional>

struct sqlite3;

class BaseRepository {
protected:
    std::shared_ptr<sqlite3> _conn;
public:
    BaseRepository(std::shared_ptr<sqlite3> conn);
    virtual ~BaseRepository();
};

#endif