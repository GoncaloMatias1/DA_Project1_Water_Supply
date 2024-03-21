//
// Created by admin1 on 04-03-2024.
//

#include "Pipe.h"

Pipe::Pipe(double maxCapacity, Vertex *origin_, Vertex *endpoint) {
    this->capacity = maxCapacity;
    this->origin = origin_;
    this->destination = endpoint;
    this->flow = 0;
}

double Pipe::getCapacity() const {
    return this->capacity;
}

Vertex* Pipe::getDestination() const {
    return this->destination;
}

const std::string& Pipe::getDestinationId() const {
    return this->destination->getCode();
}


void Pipe::setCapacity(double newCapacity) {
    this->capacity = newCapacity;
}

void Pipe::setDestination(Vertex *newDestination) {
    this->destination = newDestination;
}

void Pipe::setFlow(double newFlow) {
    this->flow = newFlow;
}

double Pipe::getFlow() const {
    return this->flow;
}

Vertex *Pipe::getOrigin() {
    return this->origin;
}

void Pipe::setOrigin(Vertex *orig) {
    this->origin = orig;
}




