#include "utils/hash.h"

using std::string;

string calculateHash(const string& text) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char *>(text.c_str()), text.length(), hash);

    char buf[2 * SHA256_DIGEST_LENGTH + 1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(buf + 2 * i, "%02x", hash[i]);
    }
    buf[2 * SHA256_DIGEST_LENGTH] = '\0';

    return string(buf);
}