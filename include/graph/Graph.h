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
#define AUGMENTING_PATH std::vector<Pipe*>

class Pipe;

class Vertex;
class City;
class WaterReservoir;
class PumpingStation;


class Graph{
protected:
    std::unordered_map<std::string, Vertex*> vertexSet;

    std::unordered_map<std::string, City*> citySet;
    std::unordered_map<std::string, WaterReservoir*> reservoirSet;
    std::unordered_map<std::string, PumpingStation*> stationSet;

    std::unordered_map<std::string, Pipe*> pipeSet;

    std::unordered_map<std::string, std::vector<AUGMENTING_PATH>> augmentingPaths;

public:
    ~Graph();
    Vertex *findVertex(const std::string& in) const;

    std::unordered_map<std::string, Vertex*> getVertexSet() const;
    std::vector<City*> getCities();
    std::vector<WaterReservoir*> getReservoirs();
    std::vector<PumpingStation*> getStations();

    Pipe* getPipe(const std::string& origin, const std::string& endpoint);

    bool addVertex(Vertex* newVertex);
    bool removeVertex(const std::string &in);

    bool addEdge(const std::string &sourc, const std::string &dest, double w);
    bool removeEdge(const std::string &source, const std::string &dest);
    void removeEdgesTo(const std::string& out);


    void addAugmentingPath(const std::string& resID, AUGMENTING_PATH path);
    std::unordered_map<std::string, std::vector<AUGMENTING_PATH>> getAugmentingPaths();
    void clearAugmentingPaths();



    // Network effiency improvements
    double calculateAverageDifference();
    double calculateVariance();
    double calculateMaxDifference();

    std::unordered_map<std::string, Pipe*> getPipeSet();




};

#endif //DA_PROJECT_23_24_GRAPH_H
