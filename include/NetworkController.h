//
// Created by admin1 on 08-03-2024.
//

#ifndef DA_PROJECT_23_24_NETWORKCONTROLLER_H
#define DA_PROJECT_23_24_NETWORKCONTROLLER_H


#include "Graph.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <limits>
#include <queue>

#define INF std::numeric_limits<double>::max()


class NetworkController{
private:
    Graph network;
    std::string dataRoot;
public:
    NetworkController(const std::string& src);
    void parseData();

    void readReservoirs();
    void readPumpingStations();
    void readCities();
    void readPipes();

    // FOr edmonds-karp
    // Generate super source that connects all sources to this with edge capacity INF
    Vertex* generateSuperSource();
    // Generate super sink that connects all sinks to this with edge capacity INF
    Vertex* generateSuperSink();
    void edmondsKarp();
    bool findAugmentingPath(Vertex* source, Vertex* sink);
    void testAndVisit(std::queue<Vertex*>&, Pipe* pipe, Vertex* dest, double residual);
    double findMinResidualAlongPath(Vertex *source, Vertex *sink);
    void augmentFlowAlongPath(Vertex* source, Vertex* sink, double f);


};

#endif //DA_PROJECT_23_24_NETWORKCONTROLLER_H
