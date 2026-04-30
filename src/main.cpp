#include <algorithm>
#include <filesystem>
#include <iostream>
#include <vector>

#include "hash/sha256.h"
#include "report/json_report.h"
#include "utils/logger.h"

namespace fs = std::filesystem;

namespace {

int run_compare_mode(const fs::path& file_a, const fs::path& file_b) {
    if (!fs::exists(file_a) || !fs::exists(file_b)) {
        std::cerr << "One or both files do not exist.\n";
        return 1;
    }

    const std::string hash_a = hash::sha256::compute_file_hash(file_a);
    const std::string hash_b = hash::sha256::compute_file_hash(file_b);

    if (hash_a.empty() || hash_b.empty()) {
        std::cerr << "Failed to compute SHA-256 hash for one or both files.\n";
        return 1;
    }

    const bool matches = (hash_a == hash_b);

    std::cout << "File A: " << file_a << "\nSHA-256: " << hash_a << "\n\n";
    std::cout << "File B: " << file_b << "\nSHA-256: " << hash_b << "\n\n";
    std::cout << (matches ? "MATCH" : "DIFFER") << "\n";

    utils::logger::log_comparison(file_a.string(), hash_a, file_b.string(), hash_b, matches);
    return 0;
}

int run_scan_mode(const fs::path& folder) {
    if (!fs::exists(folder) || !fs::is_directory(folder)) {
        std::cerr << "Scan target must be an existing directory.\n";
        return 1;
    }

    std::vector<report::json::FileHashEntry> entries;

    for (const auto& dir_entry : fs::recursive_directory_iterator(folder)) {
        if (!dir_entry.is_regular_file()) {
            continue;
        }

        const fs::path file_path = dir_entry.path();
        const std::string digest = hash::sha256::compute_file_hash(file_path);
        if (digest.empty()) {
            std::cerr << "Warning: failed to hash file: " << file_path << "\n";
            continue;
        }

        entries.push_back({fs::relative(file_path, folder).string(), digest});
    }

    std::sort(entries.begin(), entries.end(), [](const auto& lhs, const auto& rhs) {
        return lhs.path < rhs.path;
    });

    const fs::path report_path = report::json::write_scan_report(folder, entries);
    if (report_path.empty()) {
        std::cerr << "Failed to write JSON scan report.\n";
        return 1;
    }

    std::cout << "Scanned " << entries.size() << " files.\n";
    std::cout << "Report: " << report_path << "\n";
    return 0;
}

}  // namespace

int main(int argc, char* argv[]) {
    if (argc == 3 && std::string(argv[1]) == "--scan") {
        return run_scan_mode(argv[2]);
    }

    if (argc == 3) {
        return run_compare_mode(argv[1], argv[2]);
    }

    std::cerr << "Usage:\n"
              << "  " << argv[0] << " <file_a> <file_b>\n"
              << "  " << argv[0] << " --scan <folder>\n";
    return 1;
}
