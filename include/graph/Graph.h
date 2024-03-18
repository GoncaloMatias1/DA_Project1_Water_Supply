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
    std::vector<Vertex*> vertexSet;

public:
    ~Graph();
    Vertex *findVertex(const std::string& in) const;

    std::vector<Vertex*> getVertexSet() const;

    bool addVertex(Vertex* newVertex);
    bool removeVertex(const std::string &in);

    bool addEdge(const std::string &sourc, const std::string &dest, float w);
    bool removeEdge(const std::string &source, const std::string &dest);
    bool addBidirectionalEdge(const std::string &sourc, const std::string &dest, double w);

    //Info about city
    int getCityId(const std::string& cityName) const;
    int getCityPopByName(const std::string& cityName) const;

    int getCityPop(const std::string& code) const;
    int getCityDemandByName(const std::string& cityName) const;
    int getCityDemand(const std::string& code) const;


    void removeEdgesTo(const std::string& out);
};

#endif //DA_PROJECT_23_24_GRAPH_H
