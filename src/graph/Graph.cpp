//
// Created by admin1 on 04-03-2024.
//

#include "Graph.h"

Graph::~Graph(){
    for(std::pair<std::string, Vertex*> vertex: this->vertexSet){
        this->removeVertex(vertex.second->getID());
    }
};

Vertex *Graph::findVertex(const std::string &in) const {
    return vertexSet.at(in);
}

bool Graph::addVertex(Vertex* newVertex) {
    this->vertexSet.insert({newVertex->getID(), newVertex});
}

bool Graph::removeVertex(const std::string &in) {
    for(std::pair<std::string, Vertex*> pair: this->vertexSet){
        // Delete all references to dead vertex
        Vertex* currentVertex = pair.second;
        if(currentVertex->getID() != in){
            currentVertex->removePipeTo(in);
        }
    }

    Vertex* vertexToRemove = this->vertexSet.at(in);

    if(vertexToRemove != nullptr){
        this->vertexSet.erase(in);
        delete vertexToRemove;
        return true;
    }
    return false;
}


bool Graph::addEdge(const std::string &sourc, const std::string &dest, float w) {
    Vertex* source = this->vertexSet.at(sourc);
    Vertex* destination = this->vertexSet.at(dest);
    if(source != nullptr && destination != nullptr){
        Pipe* newPipe = new Pipe(w, destination);
        source->addPipe(newPipe);
        return true;
    }
    return  false;
}

bool Graph::removeEdge(const std::string &source, const std::string &dest) {
    Vertex* sourceVertex = this->vertexSet.at(source);
    if(sourceVertex != nullptr){
        return sourceVertex->removePipeTo(dest);
    }
    return  false;
}

bool Graph::addBidirectionalEdge(const std::string &sourc, const std::string &dest, double w) {
    Vertex* source = this->vertexSet.at(sourc);
    Vertex* destination = this->vertexSet.at(dest);
    if(source != nullptr && destination != nullptr){
        Pipe* sourceDestination = new Pipe(w, destination);
        Pipe* destinationSource = new Pipe(w, source);
        source->addPipe(sourceDestination);
        destination->addPipe(destinationSource);
        return true;
    }
    return  false;
}





