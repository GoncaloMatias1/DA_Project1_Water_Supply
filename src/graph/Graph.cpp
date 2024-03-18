//
// Created by admin1 on 04-03-2024.
//

#include "Graph.h"
#include "City.h"

Graph::~Graph(){
    for(auto itr = this->vertexSet.begin(); itr != this->vertexSet.end(); ){
        
        this->removeEdgesTo((*itr)->getCode());
        Vertex* toRemove = (*itr);
        itr = this->vertexSet.erase(itr);
        delete toRemove;
    }
}

Vertex *Graph::findVertex(const std::string &in) const {
    for(Vertex* v: this->vertexSet){
        if(v->getCode() == in) return v;
    }
    return nullptr;
}

bool Graph::addVertex(Vertex* newVertex) {
    this->vertexSet.push_back( newVertex);
}

bool Graph::removeVertex(const std::string &in) {
    Vertex* vertexToRemove = this->findVertex(in);
    if(vertexToRemove == nullptr) return false;
    
    for(Vertex* vertex: this->vertexSet){
        // Delete all references to dead vertex
        if(vertex->getCode() != in){
            vertex->removePipeTo(in);
            vertex->removePipeFrom(in);
        }
    }
    
    for(auto itr = this->vertexSet.begin(); itr != this->vertexSet.end();){
        if((*itr)->getCode() == in) {
            this->vertexSet.erase(itr);
            delete vertexToRemove;
            return true;
        }
        itr++;
    }
    return false;
}


bool Graph::addEdge(const std::string &sourc, const std::string &dest, float w) {
    Vertex* source = this->findVertex(sourc);
    Vertex* destination = this->findVertex(dest);


    if(source != nullptr && destination != nullptr){
        Pipe* newPipe = new Pipe(w, source, destination);
        source->addOutgoingPipe(newPipe);
        destination->addIncomingPipe(newPipe);
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
    for(Vertex* vertex: this->vertexSet){
        // Delete all references to dead vertex
        Vertex* currentVertex = vertex;
        if(currentVertex->getCode() != out){
            currentVertex->removePipeTo(out);
            currentVertex->removePipeFrom(out);
        }
    }
}

int Graph::getCityId(const std::string &cityName) const {
    for(Vertex* vertex: this->vertexSet){
        City* curr_city = dynamic_cast<City*>(vertex);
        if(curr_city != nullptr && curr_city->getName() == cityName){
            return static_cast<int>(curr_city->getID());
        }
    }
    return -1;
}

int Graph::getCityPopByName(const std::string &cityName) const {
    for(Vertex* vertex: this->vertexSet){
        City* curr_city = dynamic_cast<City*>(vertex);
        if(curr_city != nullptr  && curr_city->getName() == cityName){
            return static_cast<int>(curr_city->getPop());
        }
    }
    return -1;
}

int Graph::getCityPop(const std::string& code) const {
    City* curr_city = dynamic_cast<City*>(this->findVertex(code));

    if(curr_city != nullptr ){
        return static_cast<int>(dynamic_cast<City*>(curr_city)->getPop());
    }
    return -1;
}

int Graph::getCityDemandByName(const std::string &cityName) const {
    for(Vertex* vertex: this->vertexSet){
        City* curr_city = dynamic_cast<City*>(vertex);
        if(curr_city != nullptr  && curr_city->getName() == cityName){
            return static_cast<int>(curr_city->getDemand());
        }
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

std::vector<Vertex* > Graph::getVertexSet() const {
    return this->vertexSet;
}
