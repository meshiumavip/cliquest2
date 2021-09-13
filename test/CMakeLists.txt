add_executable(cliquest_test cliquest_test.cpp)
target_link_libraries(cliquest_test gtest_main clisystem)
target_include_directories(cliquest_test PUBLIC  ${PROJECT_SOURCE_DIR}/src/lib)