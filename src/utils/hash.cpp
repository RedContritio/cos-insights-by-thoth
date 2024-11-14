#include "utils/hash.h"

using std::string;

string calculateHash(const string& text) {
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

    return string(buf);
}