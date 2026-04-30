cmake_minimum_required(VERSION 3.16)
project(file_integrity_tool LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenSSL REQUIRED)

add_executable(file_integrity_tool
    src/main.cpp
    src/hash/sha256.cpp
    src/utils/logger.cpp
)

target_include_directories(file_integrity_tool PRIVATE include)
target_link_libraries(file_integrity_tool PRIVATE OpenSSL::Crypto)
