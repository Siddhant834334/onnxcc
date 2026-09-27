#include "cli.hpp"
#include <cxxopts.hpp>
#include <iostream>
#include <string>

namespace onnxcc::cli {

int run(int argc, char** argv) {
    // 1. If the user just typed `onnxcc` with no arguments
    if (argc <= 1) {
        std::cerr << "Error: No arguments provided.\nUsage: onnxcc <command> [options]\n";
        return 1; 
    }

    // Grab the first word the user typed after the program name
    std::string subcommand = argv[1];

    // 2. Global help menu: `onnxcc --help`
    if (subcommand == "--help") {
        std::cout << "onnxcc: Educational C++ ONNX Compiler\n"
                  << "Available subcommands: dump\n";
        return 0;
    }

    // 3. The main task: `onnxcc dump`
    if (subcommand == "dump") {
        try {
            cxxopts::Options options("onnxcc dump", "Dump ONNX model graph and details");
            
            // Define what flags are allowed for this command
            options.add_options()
                ("model", "Path to ONNX model file", cxxopts::value<std::string>())
                ("show-graph", "Show graph structure", cxxopts::value<bool>()->default_value("false"))
                ("verbose", "Enable verbose output", cxxopts::value<bool>()->default_value("false"))
                ("help", "Print dump usage");

            // Parse everything typed *after* the word "dump"
            auto result = options.parse(argc - 1, argv + 1);

            if (result.count("help")) {
                std::cout << options.help() << "\n";
                return 0; 
            }

            // Check if they forgot the required --model flag
            if (!result.count("model")) {
                std::cerr << "Error: Missing required option --model\n";
                return 1; 
            }

            // If we get here, the user provided a valid model path!
            return 0; 

        } catch (const cxxopts::exceptions::exception& e) {
            // Catch invalid flags (like if they typed --fake-flag)
            std::cerr << "Error: " << e.what() << "\n";
            return 1; 
        }
    }

    // 4. If they typed a random word like `onnxcc bogus`
    std::cerr << "Error: Unknown subcommand '" << subcommand << "'\n";
    return 1; 
}

} // namespace onnxcc::cli