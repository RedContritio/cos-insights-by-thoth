#include "repositories/base.h"

BaseRepository::BaseRepository(std::shared_ptr<sqlite3> conn) : _conn(conn) {}

BaseRepository::~BaseRepository() {}