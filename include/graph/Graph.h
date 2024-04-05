//
// Created by admin1 on 03-03-2024.
//

#ifndef DA_PROJECT_23_24_GRAPH_H
#define DA_PROJECT_23_24_GRAPH_H

#include "Vertex.h"
#include <unordered_map>
#include <vector>
#include <string>

#define PIPE_ID(origin, endpoint) (origin + "/" + endpoint)

class Vertex;
class Pipe;

class Graph{
protected:
    std::unordered_map<std::string, Vertex*> vertexSet;
    std::unordered_map<std::string, Pipe*> pipeSet;
public:
    ~Graph();
    Vertex *findVertex(const std::string& in) const;

    std::unordered_map<std::string, Vertex*> getVertexSet() const;

    bool addVertex(Vertex* newVertex);
    bool removeVertex(const std::string &in);

    bool addEdge(const std::string &sourc, const std::string &dest, float w);
    bool removeEdge(const std::string &source, const std::string &dest);
    void removeEdgesTo(const std::string& out);
    bool addBidirectionalEdge(const std::string &sourc, const std::string &dest, double w);

    //Info about city
    int getCityPop(const std::string& code) const;
    int getCityDemand(const std::string& code) const;

    Pipe* getPipe(const std::string& origin, const std::string& endpoint);

};

#endif //DA_PROJECT_23_24_GRAPH_H
