#include "report/json_report.h"

#include <chrono>
#include <fstream>
#include <iomanip>
#include <sstream>

namespace report::json {
namespace {

std::string escape_json(const std::string& input) {
    std::ostringstream escaped;
    for (char c : input) {
        switch (c) {
            case '\\':
                escaped << "\\\\";
                break;
            case '"':
                escaped << "\\\"";
                break;
            case '\n':
                escaped << "\\n";
                break;
            case '\r':
                escaped << "\\r";
                break;
            case '\t':
                escaped << "\\t";
                break;
            default:
                escaped << c;
                break;
        }
    }
    return escaped.str();
}

std::string utc_timestamp_for_filename() {
    const auto now = std::chrono::system_clock::now();
    const std::time_t now_time = std::chrono::system_clock::to_time_t(now);

    std::ostringstream out;
    out << std::put_time(std::gmtime(&now_time), "%Y%m%d_%H%M%S");
    return out.str();
}

std::string utc_timestamp_iso8601() {
    const auto now = std::chrono::system_clock::now();
    const std::time_t now_time = std::chrono::system_clock::to_time_t(now);

    std::ostringstream out;
    out << std::put_time(std::gmtime(&now_time), "%Y-%m-%dT%H:%M:%SZ");
    return out.str();
}

}  // namespace

std::filesystem::path write_scan_report(const std::filesystem::path& scanned_root,
                                        const std::vector<FileHashEntry>& entries,
                                        const std::filesystem::path& reports_dir) {
    std::filesystem::create_directories(reports_dir);

    const std::filesystem::path report_path =
        reports_dir / ("scan_report_" + utc_timestamp_for_filename() + ".json");

    std::ofstream out(report_path);
    if (!out) {
        return {};
    }

    out << "{\n";
    out << "  \"generated_at\": \"" << utc_timestamp_iso8601() << "\",\n";
    out << "  \"scanned_root\": \"" << escape_json(scanned_root.string()) << "\",\n";
    out << "  \"file_count\": " << entries.size() << ",\n";
    out << "  \"files\": [\n";

    for (size_t i = 0; i < entries.size(); ++i) {
        const auto& entry = entries[i];
        out << "    {\"path\": \"" << escape_json(entry.path)
            << "\", \"sha256\": \"" << entry.sha256 << "\"}";
        if (i + 1 != entries.size()) {
            out << ',';
        }
        out << "\n";
    }

    out << "  ]\n";
    out << "}\n";

    return report_path;
}

}  // namespace report::json
