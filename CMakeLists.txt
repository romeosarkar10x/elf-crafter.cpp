cmake_minimum_required(VERSION 3.31.6)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

set(CMAKE_EXPORT_COMPILE_COMMANDS true)

project(elf-crafter.cpp)

file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

add_executable(elf_crafter.exe ${SOURCES})

target_include_directories(elf_crafter.exe
    PUBLIC
    ${CMAKE_SOURCE_DIR}/inc
)
