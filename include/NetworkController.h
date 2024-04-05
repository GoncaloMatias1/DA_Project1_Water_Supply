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
    bool maxFlowValid;
public:
    NetworkController(const std::string& src);
    void parseData();
    void parseDataSmall();

    void readReservoirs();
    void readReservoirsSmall();
    void readPumpingStations();
    void readStationsSmall();
    void readCities();
    void readCitiesSmall();
    void readPipes();
    void readPipesSmall();
    void initializeNetwork(bool small);

    /**
    * @brief Simulates the failure of a pipe between two service points and assesses the impact on water flow.
    *
    * This function first attempts to find the specified pipe. If found, it sets its capacity to zero to simulate failure.
    * It then runs the Edmonds-Karp algorithm to recalculate the maximum flow. Finally, it iterates over cities
    * to check which ones are affected by the failure and restores the pipe's capacity.
    *
    * @param servicePointA The code of the source service point of the pipe.
    * @param servicePointB The code of the target service point of the pipe.
    */
    void simulatePipelineFailure(const std::string& servicePointA, const std::string& servicePointB);


    /**
    * @brief Searches for a pipe in the network between two service points.
    *
    * @param servicePointA The code of the source service point.
    * @param servicePointB The code of the target service point.
    * @return A pointer to the found pipe, or nullptr if not found.
    */
    Pipe* findPipe(const std::string& servicePointA, const std::string& servicePointB);

    Vertex* getVertex(const std::string& id);


    /**
 * @brief Calculates and displays the maximum water flow that can reach a specific city.
 *
 * This function modifies the network graph to direct the super sink connections temporarily to the target city and then runs the Edmonds-Karp algorithm. It calculates the maximum flow to the city, displays it, and saves the result to a file.
 *
 * @param cityCode The code of the city for which to calculate the maximum water flow.
 * @pre The network must be initialized, and the city code must correspond to an existing city in the network.
 * @post The original network configuration is restored after the calculation.
 * @note This function alters the network temporarily and should not be run concurrently with other operations that modify the network.
 */
    void edmondsKarpForCity(const std::string& cityCode);
    // FOr edmonds-karp

    /**
    * @brief Generates a super source vertex and connects all reservoirs to it.
    *
    * This ensures that there's a single source for running the Edmonds-Karp algorithm.
    * @return Pointer to the super source vertex.
    */
    Vertex* getSuperSource();

    /**
    * @brief Generates a super sink vertex and connects all cities to it.
    *
    * This ensures that there's a single sink for running the Edmonds-Karp algorithm.
    * @return Pointer to the super sink vertex.
    */
    Vertex* getSuperSink();

    /**
    * @brief Implements the Edmonds-Karp algorithm to find the maximum flow in the network.
    *
    * This function generates a super source and a super sink, initializes flow values,
    * and then iteratively finds augmenting paths and augments flow along them. It uses
    * BFS to find the shortest path in terms of the number of edges, ensuring polynomial time complexity.
    *
    * @pre Assumes that the graph has been properly initialized with vertices and edges.
    * @post The graph will contain flow values corresponding to the maximum flow from source to sink.
    *
    * @complexity O(V * E^2), where V is the number of vertices and E is the number of edges in the graph.
    */
    void edmondsKarp();

    /**
    * @brief Finds an augmenting path from the source to the sink using BFS.
    *
    * An augmenting path is a path where the residual capacity (original capacity minus current flow)
    * is greater than zero. The path is stored in each vertex's 'path' field by the BFS.
    *
    * @param source The starting vertex for the BFS.
    * @param sink The target vertex for the BFS.
    * @return True if an augmenting path is found, false otherwise.
    *
    * @complexity O(E), where E is the number of edges in the graph since BFS traverses each edge at most once.
     */
    bool findAugmentingPath(Vertex* source, Vertex* sink);


    /**
    * @brief Helper function to test whether a vertex should be visited during BFS in the context of finding an augmenting path.
    *
    * @param q Reference to the queue used for BFS.
    * @param pipe Pointer to the pipe being tested.
     * @param dest Pointer to the destination vertex.
    * @param residual The residual capacity of the pipe.
    */
    void testAndVisit(std::queue<Vertex*>&, Pipe* pipe, Vertex* dest, double residual);

    /**
    * @brief Finds the minimum residual capacity along the augmenting path found by BFS.
    *
    * @param source Pointer to the source vertex.
    * @param sink Pointer to the sink vertex.
    * @return The minimum residual capacity.
    */
    double findMinResidualAlongPath(Vertex *source, Vertex *sink);

    /**
    * @brief Augments the flow along the found augmenting path.
    *
    * This method iterates over the path stored in the vertices from the sink to the source
    * and updates the flow in each edge along the path by the minimum residual capacity.
    *
    * @param source The starting vertex of the augmenting path.
    * @param sink The ending vertex of the augmenting path.
    * @param f The amount of flow to augment along the path.
    *
    * @complexity O(P), where P is the number of edges in the augmenting path.
    */
    void augmentFlowAlongPath(Vertex* source, Vertex* sink, double f);


    // For T2.2
    /**
    * @brief Finds cities with water deficits after running the Edmonds-Karp algorithm.
    *
    * A city is in deficit if the flow into it is less than its demand.
    * @return A vector of pairs, each containing the city code and the deficit amount.
    */
    std::vector<std::pair<std::string, double>> getLowWaterCities();

    /**
    * @brief Saves the maximum flow data for each city to an output file.
    */
    void saveCityData();

    /**
    * @brief Gets the maximum flow for a specified city.
    *
    * @param city The code of the city.
    * @return A pair containing the city code and its flow value.
    */
    std::pair<std::string, double> getMaxFlowInCity(const std::string& city);

    /**
    * @brief Retrieves the flow values for all cities in the network.
    *
    * @return An unordered_map with city codes as keys and flow values as mapped values.
    */
    std::unordered_map<std::string, double> getNetworkFlow();

    // For T3.1
    std::unordered_map<std::string, std::pair<double, double>> getAffectedByReservoir( const std::string& res_id);

    /**
    * @brief Determines the impact on the network flow of removing a reservoir or a pumping station.
    *
    * @param res_id The code of the reservoir or station.
    * @return An unordered_map where each key-value pair consists of a city code and a pair of doubles representing the old and new flow values.
    */
    std::unordered_map<std::string, std::pair<double, double>> getAffectedByStation( const std::string& res_id);

};

#endif //DA_PROJECT_23_24_NETWORKCONTROLLER_H
