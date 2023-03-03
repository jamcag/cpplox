cmake_minimum_required(VERSION 3.24)
project(cpplox)

set(CMAKE_CXX_STANDARD 20)

add_executable(cpplox main.cpp token_type.h token.h token.cpp scanner.cpp scanner.h magic_enum.h lox.cpp lox.h error_handler.cpp error_handler.h)
