configure_file(onnxcc/version.h.in onnxcc/version.h @ONLY)

add_library(onnxcc_lib STATIC
    onnxcc/version.cpp
)

add_executable(onnxcc onnxcc/main.cpp)

# Link the onnxcc_lib library to the onnxcc executable
target_link_libraries(onnxcc PRIVATE onnxcc_lib)

target_link_libraries(onnxcc_lib
    PRIVATE
        protobuf::libprotobuf
        onnx_proto
)

# Include the current source directory for the onnxcc_lib target
target_include_directories(onnxcc_lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}
)

target_compile_options(onnxcc_lib PRIVATE ${ONNXCC_WARNINGS})
target_compile_options(onnxcc PRIVATE ${ONNXCC_WARNINGS})

# ==========================================
# PART A: CLI Configuration
# ==========================================

# 1. The Engine Workshop: Build the CLI library
add_library(onnxcc_cli cli/cli.cpp)

# 2. The Tools: Tell the CLI library where to find cxxopts.hpp (third_party) 
# and where to find its own header files.
target_include_directories(onnxcc_cli PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

# 3. The Assembly Line: Bolt the CLI engine into the main executable.
# (The starter code likely named your main executable 'onnxcc')
target_link_libraries(onnxcc PRIVATE onnxcc_cli)