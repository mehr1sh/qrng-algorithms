# Add GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Add test executable
add_executable(
    test_qrng
    test_qrng.cpp
)

# Link test executable with gtest and our library
target_link_libraries(
    test_qrng
    PRIVATE 
    qrng
    gtest_main
)

# Enable testing
enable_testing()

# Add test to CTest
add_test(
    NAME test_qrng
    COMMAND test_qrng
)
