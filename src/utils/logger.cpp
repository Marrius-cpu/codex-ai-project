#include "utils/logger.h"

#include <chrono>
#include <fstream>
#include <iomanip>
#include <sstream>

namespace utils::logger {

void log_comparison(const std::string& file_a,
                    const std::string& hash_a,
                    const std::string& file_b,
                    const std::string& hash_b,
                    bool matches,
                    const std::string& log_path) {
    std::ofstream log_file(log_path, std::ios::app);
    if (!log_file) {
        return;
    }

    const auto now = std::chrono::system_clock::now();
    const std::time_t now_time = std::chrono::system_clock::to_time_t(now);

    std::ostringstream timestamp;
    timestamp << std::put_time(std::gmtime(&now_time), "%Y-%m-%d %H:%M:%S UTC");

    log_file << "[" << timestamp.str() << "] "
             << "file_a=\"" << file_a << "\" "
             << "sha256_a=" << hash_a << " "
             << "file_b=\"" << file_b << "\" "
             << "sha256_b=" << hash_b << " "
             << "result=" << (matches ? "MATCH" : "DIFFER") << '\n';
}

}  // namespace utils::logger
