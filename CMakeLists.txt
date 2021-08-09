cmake_minimum_required(VERSION 3.10)
project(cligame C CXX)
add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(third_party)

# Google Testの不要なキャッシュ変数をオフにしておく
option(BUILD_GMOCK "Builds the googlemock subprojects" OFF)
option(INSTALL_GTEST "Enables installation of googletest" OFF)