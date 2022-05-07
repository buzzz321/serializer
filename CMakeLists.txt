cmake_minimum_required(VERSION 3.5)

add_compile_options(-Wall -Wextra -pedantic -Werror)

project(serializer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

add_executable(serializer main.cc)
# target_include_directories(serializer SYSTEM ${LLVM_INCLUDE_DIRS})
