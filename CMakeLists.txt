cmake_minimum_required(VERSION 3.27)
project(DA_Project_23_24)

set(CMAKE_CXX_STANDARD 14)

include_directories(Code)

add_executable(DA_Project_23_24
        Code/Menu.cpp
        Code/Menu.h
        Code/Reservoir.h
        ReadData/readData.cpp
        Code/Station.h
        Code/Pipes.h
        Code/ServicePoint.cpp
        Code/City.h
        Code/City.cpp
        main.cpp
        Code/Reservoir.cpp
        Code/Station.cpp)
