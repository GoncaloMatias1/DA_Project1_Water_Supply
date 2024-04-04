cmake_minimum_required(VERSION 3.25)
project(DA_Project_23_24)

set(CMAKE_CXX_STANDARD 14)

include_directories(
        include/graph
        include
        src/graph
        src
        data
)

add_executable(DA_Project_23_24
        include/graph/Graph.h
        include/graph/Pipe.h
        include/graph/Vertex.h
        src/graph/Graph.cpp
        src/graph/Vertex.cpp
        src/graph/Pipe.cpp
        include/graph/WaterReservoir.h
        include/graph/PumpingStation.h
        include/graph/City.h
        src/NetworkController.cpp
        src/graph/City.cpp
        main.cpp
        src/graph/PumpingStation.cpp
        src/graph/WaterReservoir.cpp
        src/graph/Menu.cpp
        include/Menu.h

)
