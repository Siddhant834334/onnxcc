#include "cli/cli.hpp"

int main(int argc, char** argv) {
    // This hands the raw terminal words directly to your processing department
    return onnxcc::cli::run(argc, argv);
}