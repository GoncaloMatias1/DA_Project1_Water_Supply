//
// Created by admin1 on 04-03-2024.
//


#include "Vertex.h"


Vertex::Vertex(const std::string & identifier) {
    this->id = identifier;
    this->adj.clear();
}

void Vertex::setID(const std::string &identifier) {
    this->id = identifier;
}

void Vertex::setAdj(const std::vector<Pipe *> &newAdj) {
    this->adj = newAdj;
}

void Vertex::addPipe(Pipe *newPipe) {
    this->adj.push_back(newPipe);
}


bool Vertex::removePipeTo(const std::string &endpoint) {
    for(auto itr = adj.begin(); itr != adj.end(); itr++){
        if((*itr)->getDestinationId() == endpoint){
            adj.erase(itr);
            return true;
        }
    }
    return false;
}



const std::string& Vertex::getID() const {
    return this->id;
}
