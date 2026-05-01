File Integrity Tool (C++ / Codex Project)

A command-line tool for verifying file integrity using SHA-256 hashing. Supports comparing two files, scanning entire directories, generating JSON reports, and logging results.

Features:

1. File Comparison Mode
   - Computes SHA-256 for two files
   - Prints both digests
   - Shows whether they match
   - Logs results to logs/integrity.log

2. Directory Scan Mode
   - Recursively scans a folder
   - Hashes every file
   - Sorts results
   - Generates a JSON report in reports/
   - Includes timestamps and relative paths

3. JSON Reporting
   - Clean, structured JSON output
   - ISO-8601 timestamps
   - Automatic escaping
   - Timestamped filenames

4. Logging
   - Timestamped log entries
   - Records comparisons
   - Appends to logs/integrity.log

5. Modular C++ Architecture
   - src/ and include/ structure
   - Hashing module
   - JSON report module
   - Logger module
   - CMake build system
   - Uses C++20 and OpenSSL

Build Instructions:

Configure the project:
cmake -S . -B build

Build the executable:
cmake --build build

The compiled binary will be located in:
build/file_integrity_tool

Usage:

Compare two files:
./file_integrity_tool fileA.txt fileB.txt

Scan a directory:
./file_integrity_tool --scan path/to/folder

JSON reports will appear in:
reports/

Logs will appear in:
logs/integrity.log

Project Structure:

include/
src/
logs/
reports/
CMakeLists.txt
README.md

Notes:

This project was developed as part of the Codex AI Challenge, focusing on AI-assisted software engineering, modular C++ design, and real-world tooling.
