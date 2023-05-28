#pragma once
#define KLANG_VERSION_MAJOR 0
#define KLANG_VERSION_MINOR 1
#define KLANG_VERSION_PATCH 0

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

#include "./Compiler.hpp"

/**
 * @brief Program arguments.
 *
 */
struct Args {
    std::string input;
    std::string output_file;
};

/**
 * @brief Get the input string and output buffer (if provided) from the command
 * line arguments.
 *
 * @param argc
 * @param argv
 * @return Args
 */
Args parse_args(int argc, char **argv);
