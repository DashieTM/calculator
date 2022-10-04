cmake_minimum_required(VERSION 3.19)

# Basic project configuration
project("Calculator"
    LANGUAGES CXX
)

# Set c++ language standard to C++20
set(CMAKE_CXX_STANDARD 20)

#[===[ LIBRARY ]===]

add_library("CalcLib" STATIC
  "lib/calc.cpp"
  "lib/digit.cpp"
)

target_include_directories("CalcLib" PUBLIC
    "lib"
)


# Specify library "CuteFramework"
# It is a header-only library, featuring no object files
add_library("CuteFramework" INTERFACE)

find_package(PkgConfig REQUIRED)

pkg_check_modules(gtkmm REQUIRED IMPORTED_TARGET gtk4 gtkmm-4.0 glibmm-2.68)

# Set the include directory paths for "CuteFramework"
# INTERFACE enables dependent targets to also use that include path
target_include_directories("CuteFramework" INTERFACE "CUTE")


#[===[ TESTS ]===]

add_executable("CalcTest"
    "test/calc_test.cpp"
)

target_link_libraries("CalcTest" PRIVATE
    "CalcLib"
    "CuteFramework"
)

add_test(NAME "CalcTest" COMMAND "CalcTest")

#[===[ APPLICATION ]===]

add_executable("Calculator"
  "app/main.cpp"
)

target_link_libraries("Calculator" PRIVATE
  "CalcLib" PUBLIC PkgConfig::gtkmm
)
