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
#define RESERVOIR_CITY(res, city) (res + "/" + city)
#define AUGMENTING_PATH std::pair<std::vector<Pipe*>, double>

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

    /**
    * @brief Destructor of the Graph class.
    *
    * Frees dynamically allocated memory for the graph's vertices.
    */
    ~Graph();

    /**
    * @brief Finds a vertex with the provided code.
    *
    * @param in The code of the vertex to find.
    * @return A pointer to the found vertex, or nullptr if not found.
    */
    Vertex *findVertex(const std::string& in) const;

    /**
    * @brief Gets the set of vertices of the graph.
    *
    * @return An unordered map of the graph's vertices.
    */
    std::unordered_map<std::string, Vertex*> getVertexSet() const;

    /**
    * @brief Gets a list of all cities in the graph.
    *
    * @return A vector of pointers to the cities in the graph.
    */
    std::vector<City*> getCities();

    /**
    * @brief Gets a list of all water reservoirs in the graph.
    *
    * @return A vector of pointers to the water reservoirs in the graph.
    */
    std::vector<WaterReservoir*> getReservoirs();

    /**
    * @brief Gets a list of all pumping stations in the graph.
    *
    * @return A vector of pointers to the pumping stations in the graph.
    */
    std::vector<PumpingStation*> getStations();

    /**
    * @brief Gets a pipe between two vertices.
    *
    * @param origin The code of the origin vertex.
    * @param endpoint The code of the destination vertex.
    * @return A pointer to the pipe between the specified vertices.
    */
    Pipe* getPipe(const std::string& origin, const std::string& endpoint);

    /**
    * @brief Adds a vertex to the graph.
    *
    * @param newVertex Pointer to the vertex to be added.
    * @return True if the vertex is added successfully, false otherwise.
    */
    bool addVertex(Vertex* newVertex);

    /**
    * @brief Removes a vertex from the graph.
    *
    * @param in The code of the vertex to be removed.
    * @return True if the vertex is removed successfully, false otherwise.
    */
    bool removeVertex(const std::string &in);

    /**
    * @brief Adds an edge (pipe) between two vertices.
    *
    * @param sourc The code of the source vertex.
    * @param dest The code of the destination vertex.
    * @param w The weight (capacity) of the edge.
    * @return True if the edge is added successfully, false otherwise.
    */
    bool addEdge(const std::string &sourc, const std::string &dest, double w);

    /**
    * @brief Removes an edge (pipe) between two vertices.
    *
    * @param source The code of the source vertex.
    * @param dest The code of the destination vertex.
    * @return True if the edge is removed successfully, false otherwise.
    */
    bool removeEdge(const std::string &source, const std::string &dest);

    /**
    * @brief Removes all edges connected to a specified vertex.
    *
    * @param out The code of the vertex to remove edges from.
    */
    void removeEdgesTo(const std::string& out);

    /**
    * @brief Adds a bidirectional edge (pipe) between two vertices.
    *
    * @param sourc The code of the source vertex.
    * @param dest The code of the destination vertex.
    * @param w The weight (capacity) of the edge.
    * @return True if the bidirectional edge is added successfully, false otherwise.
    */
    bool addBidirectionalEdge(const std::string &sourc, const std::string &dest, double w);

    /**
    * @brief Gets the population of a city with the specified code.
    *
    * @param code The code of the city.
    * @return The population of the city, or -1 if not found.
    */
    int getCityPop(const std::string& code) const;

    /**
    * @brief Gets the demand of a city with the specified code.
    *
    * @param code The code of the city.
    * @return The demand of the city, or -1 if not found.
    */
    int getCityDemand(const std::string& code) const;

    /**
    * @brief Adds an augmenting path to the graph.
    *
    * @param resCityID The ID of the reservoir-city pair.
    * @param path The augmenting path to add.
    */
    void addAugmentingPath(const std::string& resCityID,AUGMENTING_PATH path);

    /**
    * @brief Clears all augmenting paths from the graph.
    */
    void clearAugmentingPaths();

    // Network effiency improvements
    /**
    * @brief Calculates the average difference between capacity and flow in all pipes.
    *
    * @return The average difference.
    */
    double calculateAverageDifference();

    /**
    * @brief Calculates the variance of differences between capacity and flow in all pipes.
    *
    * @return The variance.
    */
    double calculateVariance();

    /**
    * @brief Calculates the maximum difference between capacity and flow in all pipes.
    *
    * @return The maximum difference.
    */
    double calculateMaxDifference();

    /**
    * @brief Gets the set of pipes in the graph.
    *
    * @return An unordered map of pipes in the graph.
    */
    std::unordered_map<std::string, Pipe*> getPipeSet();




};

#endif //DA_PROJECT_23_24_GRAPH_H
