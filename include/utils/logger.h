#pragma once

#include <string>

namespace utils::logger {

void log_comparison(const std::string& file_a,
                    const std::string& hash_a,
                    const std::string& file_b,
                    const std::string& hash_b,
                    bool matches,
                    const std::string& log_path = "logs/integrity.log");

}  // namespace utils::logger
