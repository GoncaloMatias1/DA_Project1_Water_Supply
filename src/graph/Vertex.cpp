//
// Created by admin1 on 04-03-2024.
//


#include "Vertex.h"

Vertex::Vertex(const std::string & identifier) {
    this->code = identifier;
    this->incoming.clear();
    this->outgoing.clear();
}

void Vertex::setCode(const std::string &identifier) {
    this->code = identifier;
}

void Vertex::setOutgoing(const std::vector<Pipe *> &newAdj) {
    this->outgoing = newAdj;
}
void Vertex::setIncoming(const std::vector<Pipe *> &newAdj) {
    this->incoming = newAdj;
}

void Vertex::addOutgoingPipe(Pipe *newPipe) {
    this->outgoing.push_back(newPipe);
}

void Vertex::addIncomingPipe(Pipe *newPipe) {
    this->incoming.push_back(newPipe);
}

bool Vertex::removePipeTo(const std::string &endpoint) {
    for(auto itr = outgoing.begin(); itr != outgoing.end(); itr++){
        if((*itr)->getDestinationId() == endpoint){
            outgoing.erase(itr);
            return true;
        }
    }
    return false;
}

bool Vertex::removePipeFrom(const std::string &origin) {
    for(auto itr = incoming.begin(); itr != incoming.end(); itr++){
        if((*itr)->getDestinationId() == origin){
            incoming.erase(itr);
            return true;
        }
    }
    return false;
}

const std::string& Vertex::getCode() const {
    return this->code;
}

void Vertex::setVisited(bool newSt) {
    this->visited = newSt;
}

bool Vertex::isVisited() const {
    return this->visited;
}

void Vertex::setProcessing(bool proc) {
    this->processing = proc;
}

bool Vertex::isProcessing() const {
    return this->processing;
}

void Vertex::setPath(Pipe *parent) {
    this->path = parent;
}

Pipe *Vertex::getPath() const {
    return this->path;
}

VertexType Vertex::getType() const {
    return VertexType::VirtualVertex;
}

std::vector<Pipe *> Vertex::getIncoming() const {
    return this->incoming;
}

std::vector<Pipe *> Vertex::getOutgoing() const {
    return this->outgoing;
}

void Vertex::clearIncoming() {
    this->incoming.clear();
}

void Vertex::setType(VertexType type) {
    this->vertexType = type;
}




