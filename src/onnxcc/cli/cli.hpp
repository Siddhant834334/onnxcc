#pragma once

namespace onnxcc::cli {
    // Takes the raw terminal words (argc, argv) and returns an exit code (0 = success, 1 = fail)
    int run(int argc, char** argv);
}