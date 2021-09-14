add_executable(clisystemUT clisystemUT.cpp)
target_link_libraries(clisystemUT gtest_main clisystem)
target_include_directories(clisystemUT PUBLIC  ${PROJECT_SOURCE_DIR}/src/lib)

add_executable(clisceneUT clisceneUT.cpp)
target_link_libraries(clisceneUT gtest_main clisystem)
target_include_directories(clisceneUT PUBLIC  ${PROJECT_SOURCE_DIR}/src/lib)