#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "hash/sha256.h"
#include "utils/logger.h"

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <file_a> <file_b>\n";
        return 1;
    }

    const fs::path fileA = argv[1];
    const fs::path fileB = argv[2];

    if (!fs::exists(fileA) || !fs::exists(fileB)) {
        std::cerr << "One or both files do not exist.\n";
        return 1;
    }

    const std::string hashA = hash::sha256::compute_file_hash(fileA);
    const std::string hashB = hash::sha256::compute_file_hash(fileB);

    if (hashA.empty() || hashB.empty()) {
        std::cerr << "Failed to compute SHA-256 hash for one or both files.\n";
        return 1;
    }

    const bool matches = (hashA == hashB);

    std::cout << "File A: " << fileA << "\nSHA-256: " << hashA << "\n\n";
    std::cout << "File B: " << fileB << "\nSHA-256: " << hashB << "\n\n";
    std::cout << (matches ? "MATCH" : "DIFFER") << "\n";

    utils::logger::log_comparison(fileA.string(), hashA, fileB.string(), hashB, matches);

    return 0;
}
