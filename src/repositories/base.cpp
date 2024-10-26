#include "repositories/base.h"

BaseRepository::BaseRepository(std::shared_ptr<sqlite3> dbConnection) : db(dbConnection) {}

BaseRepository::~BaseRepository() {}