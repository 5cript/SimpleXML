# Version check
cmake_minimum_required (VERSION 3.0)

# Project
project(SimpleXML)

# Add files
file(GLOB sources "xml_parse/*.cpp" "xmlify/*.cpp" "utility/*.cpp")

# Add library
add_library(SimpleXML STATIC ${sources})

# Compiler Options
target_compile_options(SimpleXML PRIVATE -fexceptions -std=c++14 -O3 -Wall -pedantic-errors -pedantic)