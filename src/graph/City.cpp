//
// Created by admin1 on 08-03-2024.
//
#include "City.h"

City::City(const std::string& vertexId, const std::string &name, unsigned int id, double demand_,
           unsigned int population) : Vertex(vertexId){
    this->cityName = name;
    this->cityId = id;
    this->pop = population;
    this->demand = demand_;
}

