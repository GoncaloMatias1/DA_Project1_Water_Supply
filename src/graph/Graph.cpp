//
// Created by admin1 on 04-03-2024.
//

#include <iostream>
#include "Graph.h"
#include "City.h"

Graph::~Graph(){
    for(auto itr = this->vertexSet.begin(); itr != this->vertexSet.end(); ){
        Vertex* currentVertex = itr->second;
        this->removeEdgesTo(currentVertex->getCode());
        itr = this->vertexSet.erase(itr);
        delete currentVertex;
    }
}

Vertex *Graph::findVertex(const std::string &in) const {
    auto it = this->vertexSet.find(in);
    if (it != this->vertexSet.end()) {
        // Key exists in the map, return the corresponding value (Vertex*)
        return it->second;
    } else {
        // Key not found, return nullptr or handle accordingly
        return nullptr; // Or throw an exception, log an error, etc.
    }
}

bool Graph::addVertex(Vertex* newVertex) {
    if(newVertex->getCode() == "SuperSource");
    this->vertexSet.emplace(newVertex->getCode(), newVertex);
}

bool Graph::removeVertex(const std::string &in) {
    Vertex* vertexToRemove = this->findVertex(in);
    if(vertexToRemove == nullptr) return false;


    for(std::pair<std::string, Vertex*> vertexPair: this->vertexSet){
        // Delete all references to dead vertex
        Vertex* currentVertex = vertexPair.second;
        if(vertexPair.first != in){
            currentVertex->removePipeTo(in);
            currentVertex->removePipeFrom(in);
        }
    }
    
    return this->vertexSet.erase(in) != 0;
}


bool Graph::addEdge(const std::string &sourc, const std::string &dest, float w) {
    Vertex* source = this->findVertex(sourc);
    Vertex* destination = this->findVertex(dest);

    if(source != nullptr && destination != nullptr){
        Pipe* newPipe = new Pipe(w, source, destination);
        source->addOutgoingPipe(newPipe);
        destination->addIncomingPipe(newPipe);
        this->pipeSet[PIPE_ID(sourc, dest)] = newPipe;
        return true;
    }
    return  false;
}

bool Graph::removeEdge(const std::string &source, const std::string &dest) {
    Vertex* sourceVertex = this->findVertex(source);
    Vertex* destinationVertex = this->findVertex(dest);
    if(sourceVertex != nullptr && destinationVertex != nullptr){
        return sourceVertex->removePipeTo(dest) && destinationVertex->removePipeFrom(source);
    }
    return false;
}

bool Graph::addBidirectionalEdge(const std::string &sourc, const std::string &dest, double w) {
    Vertex* source = this->findVertex(sourc);
    Vertex* destination = this->findVertex(dest);
    if(source != nullptr && destination != nullptr){
        this->addEdge(sourc, dest, w);
        this->addEdge(dest, sourc, w);
        return true;
    }
    return  false;
}

void Graph::removeEdgesTo(const std::string &out) {
    for(std::pair<std::string, Vertex*> vertexPair: this->vertexSet){

        // Delete all references to dead vertex
        Vertex* currentVertex = vertexPair.second;
        if(currentVertex->getCode() != out){
            currentVertex->removePipeTo(out);
            currentVertex->removePipeFrom(out);
        }
    }
}

int Graph::getCityPop(const std::string& code) const {
    City* curr_city = dynamic_cast<City*>(this->findVertex(code));

    if(curr_city != nullptr ){
        return static_cast<int>(dynamic_cast<City*>(curr_city)->getPop());
    }
    return -1;
}


int Graph::getCityDemand(const std::string& code) const {
    City* curr_city = dynamic_cast<City*>(this->findVertex(code));

    if(curr_city != nullptr ){
        return static_cast<int>(dynamic_cast<City*>(curr_city)->getDemand());
    }
    return -1;
}

std::unordered_map<std::string, Vertex*> Graph::getVertexSet() const {
    return this->vertexSet;
}

Pipe *Graph::getPipe(const std::string &origin, const std::string &endpoint) {
    return pipeSet[PIPE_ID(origin, endpoint)];
}
