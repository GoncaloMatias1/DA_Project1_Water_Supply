//
// Created by admin1 on 03-03-2024.
//

#ifndef DA_PROJECT_23_24_GRAPH_H
#define DA_PROJECT_23_24_GRAPH_H

#include "Vertex.h"

class Graph{
private:
    std::vector<Vertex*> graph;
public:
    Graph();

    // Class getters
    std::vector<Vertex*> getVertexSet() const;

    // Class setters
    void setVertexSet(const std::vector<Vertex*>& newSet);


};

#endif //DA_PROJECT_23_24_GRAPH_H
