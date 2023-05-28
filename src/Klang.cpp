#include "./Klang.hpp"

void log_error(std::string error) { throw std::runtime_error(error); }

void print_usage() {
    log_error("Usage: klang -i <input_file> -o <output_file>");
}

Args parse_args(int argc, char **argv) {
    Args args;

    // Get string views of the command line arguments
    std::vector<std::string_view> cmd_args(argv, argv + argc);
    if (cmd_args.size() != 3 && cmd_args.size() != 5) {
        print_usage();
    }

    // Read the contents of the input file
    if (cmd_args[1] == "-i") {
        std::ifstream file(cmd_args[2].data(), std::ios::in);
        std::stringstream stream;
        if (!file.is_open()) {
            log_error("Could not open input file: " + std::string(cmd_args[2]));
        }
        stream << file.rdbuf();
        args.input = stream.str();
    } else {
        print_usage();
    }

    // Optionally, open the output file
    if (cmd_args.size() == 5) {
        if (cmd_args[3] == "-o") {
            args.output_file = cmd_args[4].data();
        } else {
            print_usage();
        }
    }
    return args;
}

int main(int argc, char **argv) {
    try {
        Args args = parse_args(argc, argv);

        // TODO: Run compiler arguments
        std::string compiled;

        // Write to output buffer
        if (args.output_file.length() > 0) {
            std::ofstream file(args.output_file, std::ios::out);
            if (!file.is_open()) {
                log_error("Could not open output file: " + args.output_file);
            }
            file << compiled;
        } else {
            std::cout << compiled << std::endl;
        }
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}