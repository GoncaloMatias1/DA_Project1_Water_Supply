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

void City::setName(const std::string &name) {
    this->cityName = name;
}

void City::setID(unsigned int id) {
    this->cityId = id;
}

void City::setPop(unsigned int pop_) {
    this->pop = pop_;
}

void City::setDemand(double demand_) {
    this->demand = demand_;
}

const std::string &City::getName() const {
    return this->cityName;
}

unsigned int City::getID() const {
    return this->cityId;
}

unsigned int City::getPop() const {
    return this->pop;
}

double City::getDemand() const {
    return this->demand;
}

VertexType City::getType() const {
    return VertexType::CityVertex;
}

City::City(City *city): Vertex(city->getCode()){
    this->pop = city->getPop();
    this->cityName = city->getName();
    this->cityId = city->getID();
    this->demand = city->getDemand();
}
