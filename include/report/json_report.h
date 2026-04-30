#pragma once

#include <filesystem>
#include <string>
#include <vector>

namespace report::json {

struct FileHashEntry {
    std::string path;
    std::string sha256;
};

std::filesystem::path write_scan_report(
    const std::filesystem::path& scanned_root,
    const std::vector<FileHashEntry>& entries,
    const std::filesystem::path& reports_dir = "reports");

}  // namespace report::json
