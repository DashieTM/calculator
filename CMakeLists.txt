
cmake_minimum_required(VERSION 3.10)

# specify the C++ standard
#set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_STANDARD_REQUIRED True)
project(GTKTest)
add_executable(GTKTest main.cpp)
find_package(PkgConfig REQUIRED)
pkg_check_modules(gtkmm REQUIRED IMPORTED_TARGET gtk4 gtkmm-4.0 glibmm-2.68)
target_link_libraries(GTKTest PUBLIC PkgConfig::gtkmm)
#target_include_directories(
#                            GTKTest PUBLIC
#                           "${PROJECT_BINARY_DIR}"
#                           "${PROJECT_SOURCE_DIR}"
#                          )
