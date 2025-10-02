cmake_minimum_required(VERSION 3.16)
set(CMAKE_OSX_SYSROOT macosx)
project(prog_exe CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Problem2
add_executable(Problem2 Problem2/engine.cpp)

# Problem3
add_executable(Problem3 Problem3/main.cpp)

# Problem5
add_executable(osd3 Problem5/program/osd-3.cpp)
add_executable(jacobi Problem5/program/jacobi.cpp)

# includeディレクトリが必要な場合
# target_include_directories(osd3 PRIVATE Problem5/program)