add_executable(test_turing)

add_subdirectory(data)

target_link_libraries(test_turing turinglib coverage_config gtest_main)

add_test(TARGET ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test_turing)
