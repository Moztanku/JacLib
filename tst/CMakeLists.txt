find_package(GTest REQUIRED)

set(TESTS_NAME ${PROJECT_NAME}_tests)

add_executable(${TESTS_NAME})

# Need to move compiled .dll to the same directory as the tests for Windows
if (MSVC AND BUILD_SHARED_LIBS)
    add_custom_command(
        TARGET ${TESTS_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE:${PROJECT_NAME}>"
        "$<TARGET_FILE_DIR:${TESTS_NAME}>")
endif()

target_include_directories(${TESTS_NAME}
    PRIVATE
    fixtures)

target_sources(${TESTS_NAME}
    PRIVATE
    Types.cpp
    Print.cpp)

if(${PROJECT_NAME}_GRAPHICS)
    target_sources(${TESTS_NAME}
        PRIVATE
        graphics/Window.cpp)
endif()

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
