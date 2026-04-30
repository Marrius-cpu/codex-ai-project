#include "hash/sha256.h"

#include <array>
#include <fstream>
#include <iomanip>
#include <sstream>

#include <openssl/sha.h>

namespace hash::sha256 {

std::string compute_file_hash(const std::filesystem::path& file_path) {
    std::ifstream file(file_path, std::ios::binary);
    if (!file) {
        return {};
    }

    SHA256_CTX ctx;
    SHA256_Init(&ctx);

    std::array<char, 8192> buffer{};
    while (file.good()) {
        file.read(buffer.data(), static_cast<std::streamsize>(buffer.size()));
        const std::streamsize bytes_read = file.gcount();
        if (bytes_read > 0) {
            SHA256_Update(&ctx, buffer.data(), static_cast<size_t>(bytes_read));
        }
    }

    std::array<unsigned char, SHA256_DIGEST_LENGTH> digest{};
    SHA256_Final(digest.data(), &ctx);

    std::ostringstream hex_stream;
    hex_stream << std::hex << std::setfill('0');
    for (unsigned char byte : digest) {
        hex_stream << std::setw(2) << static_cast<int>(byte);
    }

    return hex_stream.str();
}

}  // namespace hash::sha256
