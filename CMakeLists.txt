cmake_minimum_required(VERSION 3.10)
project(Final_Project___mmn_14 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Final_Project___mmn_14
        assembler.c
        Data.c
        Data.h
        first_pass.h
        firstPass.c
        output_creation.h
        outputCreation.c
        parsing.c
        parsing.h
        second_pass.h
        secondPass.c)
