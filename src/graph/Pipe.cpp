//
// Created by admin1 on 04-03-2024.
//

#include "Pipe.h"

Pipe::Pipe(float maxCapacity, Vertex *endpoint) {
    this->capacity = maxCapacity;
    this->destination = endpoint;
}

double Pipe::getCapacity() const {
    return this->capacity;
}

Vertex* Pipe::getDestination() const {
    return this->destination;
}

const std::string& Pipe::getDestinationId() const {
    return this->destination->getID();
}


void Pipe::setCapacity(double newCapacity) {
    this->capacity = newCapacity;
}

void Pipe::setDestination(Vertex *newDestination) {
    this->destination = newDestination;
}
