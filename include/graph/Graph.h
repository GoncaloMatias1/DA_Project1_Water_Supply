//
// Created by admin1 on 03-03-2024.
//

#ifndef DA_PROJECT_23_24_GRAPH_H
#define DA_PROJECT_23_24_GRAPH_H

#include "Vertex.h"
#include <unordered_map>
#include <vector>
#include <string>

class Vertex;
class Pipe;

class Graph{
protected:
    std::unordered_map<std::string, Vertex*> vertexSet;

public:
    ~Graph();
    Vertex *findVertex(const std::string& in) const;


    bool addVertex(Vertex* newVertex);
    bool removeVertex(const std::string &in);

    bool addEdge(const std::string &sourc, const std::string &dest, float w);
    bool removeEdge(const std::string &source, const std::string &dest);
    bool addBidirectionalEdge(const std::string &sourc, const std::string &dest, double w);

    int getNumVertex() const;
    std::vector<Vertex *> getVertexSet() const;

};

#endif //DA_PROJECT_23_24_GRAPH_H
