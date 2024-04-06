//
// Created by admin1 on 04-03-2024.
//

#include <iostream>
#include "Graph.h"
#include "Vertex.h"
#include "City.h"
#include "WaterReservoir.h"
#include "PumpingStation.h"


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
        return it->second;
    } else {
        return nullptr;
    }
}

bool Graph::addVertex(Vertex* newVertex) {
    switch (newVertex->getType()) {
        case CityVertex:
            this->citySet[newVertex->getCode()] = dynamic_cast<City*>(newVertex);
            break;
        case ReservoirVertex:
            this->reservoirSet[newVertex->getCode()] = dynamic_cast<WaterReservoir*>(newVertex);
            break;
        case PumpingStationVertex:
            this->stationSet[newVertex->getCode()] = dynamic_cast<PumpingStation*>(newVertex);
            break;
        case VirtualVertex:
            // SuperSink/SuperSource
            break;
    }
    this->vertexSet.emplace(newVertex->getCode(), newVertex);
    return true;
}

bool Graph::removeVertex(const std::string &in) {
    Vertex* vertexToRemove = this->findVertex(in);
    if(vertexToRemove == nullptr) return false;

    this->citySet.erase(in);
    this->reservoirSet.erase(in);
    this->stationSet.erase(in);

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


bool Graph::addEdge(const std::string &sourc, const std::string &dest, double w) {
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


/**
 * For partial edmonds karp (NOT IMPLEMENTED)
 */
void Graph::clearAugmentingPaths() {
    this->augmentingPaths.clear();
}

void Graph::addAugmentingPath(const std::string &resCityID, AUGMENTING_PATH path) {
    auto currentResCity = this->augmentingPaths.find(resCityID);

    // Reservoir-city already has atleast one augmenting path
    if(currentResCity != this->augmentingPaths.end()){
        currentResCity->second.push_back(path);
    }
    // Reservoir-city is not present in map
    else{
        this->augmentingPaths[resCityID] = {path};
    }

}

std::vector<City *> Graph::getCities() {
    std::vector<City *> result;
    result.reserve(this->citySet.size());

    for(std::pair<std::string, City*> pair: this->citySet){
        result.push_back(pair.second);
    }
    return result;
}

std::vector<WaterReservoir *> Graph::getReservoirs() {
    std::vector<WaterReservoir *> result;
    result.reserve(this->reservoirSet.size());

    for(std::pair<std::string, WaterReservoir*> pair: this->reservoirSet){
        result.push_back(pair.second);
    }
    return result;
}

std::vector<PumpingStation *> Graph::getStations() {
    std::vector<PumpingStation *> result;
    result.reserve(this->stationSet.size());

    for(std::pair<std::string, PumpingStation*> pair: this->stationSet){
        result.push_back(pair.second);
    }
    return result;
}


double Graph::calculateAverageDifference() {
    double diffs = 0;
    for(std::pair<std::string, Pipe*> pipe: this->pipeSet){
        diffs += pipe.second->getCapacity() - pipe.second->getFlow();
    }
    return diffs / static_cast<double>(pipeSet.size());
}

double Graph::calculateVariance() {
    double mean = this->calculateAverageDifference();
    double variance = 0;

    for(std::pair<std::string, Pipe*> pipe: this->pipeSet){
        double curr_diff = pipe.second->getCapacity() - pipe.second->getFlow();
        variance += (curr_diff - mean) * (curr_diff - mean);

    }
    return variance / static_cast<double>(pipeSet.size());
}

double Graph::calculateMaxDifference() {
    double max = INT32_MIN;
    for(std::pair<std::string, Pipe*> pipe: this->pipeSet){
        double curr_diff = pipe.second->getCapacity() - pipe.second->getFlow();
        if(curr_diff > max) max = curr_diff;
    }
    return max;
}

std::unordered_map<std::string, Pipe *> Graph::getPipeSet() {
    return this->pipeSet;
}

