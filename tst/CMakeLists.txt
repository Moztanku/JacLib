find_package(GTest REQUIRED)

set(TESTS_NAME ${PROJECT_NAME}_tests)

add_executable(${TESTS_NAME})

target_sources(${TESTS_NAME}
    PRIVATE
    Types.cpp)

target_link_libraries(${TESTS_NAME}
    PRIVATE
    GTest::gtest
    GTest::gtest_main
    ${PROJECT_NAME})

target_compile_options(${TESTS_NAME}
    PRIVATE
    ${compiler_flags})

include(GoogleTest)

gtest_discover_tests(${TESTS_NAME})
