#pragma once

#include <filesystem>
#include <string>

namespace hash::sha256 {

std::string compute_file_hash(const std::filesystem::path& file_path);

}  // namespace hash::sha256
