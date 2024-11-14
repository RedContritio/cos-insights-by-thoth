#ifndef UTILS_HASH_H
#define UTILS_HASH_H

#include <string>
#include <openssl/sha.h>

std::string calculateHash(const std::string& text);

#endif