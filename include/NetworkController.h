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
    Graph network; /**< Graph representing the network */
    std::string dataRoot; /**< Root directory containing data files */
    bool maxFlowValid; /**< Flag indicating whether maximum flow calculation is valid */
public:
    /**
     * @brief Constructor for NetworkController class.
     *
     * Initializes the dataRoot attribute with the provided source string, which represents the root directory of the data.
     * It also sets the maxFlowValid attribute to false.
     *
     * @param src The root directory containing data files.
     */
    NetworkController(const std::string& src);

    /**
     * @brief Parses data from files to initialize the network graph.
     *
     * Reads data for cities, reservoirs, pumping stations, and pipes from the datasets.
     * It calls individual functions for each data type and handles any exceptions that may occur during parsing.
     * Finally, it prints a completion message.
     */
    void parseData();

    /**
     * @brief Parses a small amount of data from files to initialize the network graph.
     *
     * Reads data for cities, reservoirs, stations, and pipes from small-sized datasets.
     * It calls individual functions for each data type and handles any exceptions that may occur during parsing.
     * Finally, it prints a completion message.
     */
    void parseDataSmall();

    /**
     * @brief Reads reservoir data from files and adds reservoir vertices to the graph.
     *
     * Reads reservoir data from a CSV file located at a specific path.
     * It opens the file and reads each line, parsing information about each reservoir, such as its name, municipality, ID, code, and maximum delivery.
     * It then creates a WaterReservoir object with this information and adds it to the network.
     * If the file cannot be opened, it throws an invalid argument exception.

     */
    void readReservoirs();

    /**
     * @brief Reads a small amount of reservoir data from files and adds reservoir vertices to the graph.
     *
     * Reads pumping station data from a CSV file located at a specific path.
     * It opens the file and reads each line, parsing information about each station, such as its ID and code.
     * It then creates a PumpingStation object with this information and adds it to the network.
     * If the file cannot be opened, it throws an invalid argument exception.
     */
    void readReservoirsSmall();

    /**
     * @brief Reads pumping station data from files and adds pumping station vertices to the graph.
     *
     * Reads pumping station data from a CSV file located at a specific path.
     * It opens the file and reads each line, parsing information about each station, such as its ID and code.
     * It then creates a PumpingStation object with this information and adds it to the network.
     * If the file cannot be opened, it throws an invalid argument exception.
     */
    void readPumpingStations();

    /**
     * @brief Reads a small amount of pumping station data from files and adds pumping station vertices to the graph.
     *
     * Reads station data from a CSV file located at a specific path. It opens the file and reads each line, parsing
     * information about each station, such as its ID and code. It then creates a PumpingStation object with this
     * information and adds it to the network. If the file cannot be opened, it prints an error message and returns.
     * If a line has insufficient data or empty ID and code, it skips that line.
     */
    void readStationsSmall();

    /**
     * @brief Reads city data from files and adds city vertices to the graph.
     *
     * Reads city data from a CSV file located at a specified path. It opens the file and reads each line, parsing
     * information about each city such as name, ID, code, demand, and population.
     * It then creates a City object with this information and adds it to the network.
     * If the file cannot be opened, it throws an invalid_argument exception.
     */
    void readCities();

    /**
     * @brief Reads a small amount of city data from files and adds city vertices to the graph.
     *
     *  Reads city data from a CSV file located at a specific path. It opens the file and reads each line, parsing
     *  information about each city such as name, ID, code, demand, and population. It then creates a City object with
     *  this information and adds it to the network. If the file cannot be opened, it prints an error message.
     */
    void readCitiesSmall();

    /**
     * @brief Reads pipe data from files and adds pipes to connect vertices in the graph.
     *
     * Reads pipe data from a CSV file specified by dataRoot. It opens the file and reads each line, parsing information
     * about each pipe such as service points, capacity, and direction. It then adds edges to the network based on this information.
     * If any endpoint of the pipe doesn't exist in the network, it throws an exception.
     */
    void readPipes();

    /**
     * @brief Reads a small amount of pipe data from files and adds pipes to connect vertices in the graph.
     *
     * Reads pipe data for a small network from a CSV file. It iterates over each line of the file, extracts information
     * about each pipe (such as service points, capacity, and direction), and adds edges to the network accordingly.
     * If any endpoint of the pipe doesn't exist in the network, it throws an exception.
     */
    void readPipesSmall();

    /**
     * @brief Initializes the network graph.
     *
     * Sets up the network according to the specified mode, either small or large.
     * If the small parameter is true, it calls parseDataSmall to parse the data for a small network, otherwise it calls parseData for a large network.
     * After parsing the data, it applies the Edmonds-Karp algorithm to find the maximum flow in the network using edmondsKarp.
     *
     * @param small Flag indicating whether to initialize a small version of the network.
     */
    void initializeNetwork(bool small);


    std::unordered_map<std::string, std::pair<double, double>> simulatePipelineFailure(const std::string& servicePointA, const std::string& servicePointB);
    Pipe* findPipe(const std::string& servicePointA, const std::string& servicePointB);

    /**
     * @brief Retrieves a vertex from the graph by its identifier.
     *
     * Uses the findVertex method of the network object to search for the vertex with the specified ID
     *
     * @param id The identifier of the vertex to retrieve.
     * @return A pointer to the vertex if found, nullptr otherwise.
     */
    Vertex* getVertex(const std::string& id);

    // FOr edmonds-karp

    // Generate super source that connects all sources to this with edge capacity INF
    /**
     * @brief Generates a super source vertex that connects all sources to it with edge capacity INF.
     *
     * Creates a super source vertex if it doesn't already exist in the network.
     * It connects this super source vertex to all water reservoirs by creating pipes from the super source to
     * each reservoir with capacities equal to their maximum delivery.
     *
     * @return A pointer to the super source vertex.
     */
    Vertex* getSuperSource();

    // Generate super sink that connects all sinks to this with edge capacity INF
    /**
     * @brief Generates a super sink vertex that connects all sinks to it with edge capacity INF.
     *
     * Ensures the existence of a vertex representing the super sink in the network.
     * If it doesn't exist, it creates one with the code "SuperSink" and connects it to all cities in the network with
     * pipes having capacities equal to each city's demand.
     *
     * @return A pointer to the super sink vertex.
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
     * @brief Tests and visits vertices along a path to determine the residual flow.
     *
     * Serves as a helper function within the BFS traversal process of the Edmonds-Karp algorithm, determining whether
     * adjacent vertices should be visited based on residual capacity and visitation status.
     *
     * @param q A queue of vertices to visit.
     * @param pipe The pipe connecting the vertices.
     * @param dest The destination vertex.
     * @param residual The residual flow.
     */
    void testAndVisit(std::queue<Vertex*>&, Pipe* pipe, Vertex* dest, double residual);

    /**
     * @brief Finds the minimum residual along a path between a source and a sink.
     *
     * Calculates the minimum residual capacity along the augmenting path found during the Edmonds-Karp algorithm.
     * It iterates through the path from the sink to the source, determining the minimum residual capacity
     * based on the capacities and flows of the pipes along the path.
     *
     * @param source The source vertex.
     * @param sink The sink vertex.
     * @return The minimum residual along the path.
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
     * @brief Retrieves cities with low water levels.
     *
     * Identifies cities experiencing water shortage by comparing their demand with the current flow distribution after
     * running the Edmonds-Karp algorithm. It retrieves the super sink vertex and checks incoming pipes.
     * For cities with demand exceeding flow, it records the shortfall.
     *
     * @return A vector of pairs containing city codes and their respective water levels.
     */
    std::vector<std::pair<std::string, double>> getLowWaterCities();

    /**
     * @brief Saves city data to files.
     *
     * Stores data about city flows in a text file named "max_flow_network.txt" located in the output directory.
     * It first retrieves the super sink vertex to access incoming pipes. Then, it opens the output file and writes a
     * header indicating the format of the data to be stored. For each incoming pipe, representing a city, it retrieves
     * the city's code, demand, and flow, and writes this information to the file.
     * If the file cannot be opened, it displays an error message.
     */
    void saveCityData();

    /**
     * @brief Retrieves the maximum flow in a city.
     *
     * Calculates the maximum flow reaching a given city within the network.
     * It first ensures the network's maximum flow values are up-to-date by invoking edmondsKarp.
     * Then, it retrieves the city vertex. If the city doesn't exist, it returns a pair with the city name and -1.
     * Otherwise, it checks outgoing pipes from the city to find the flow to the super sink.
     *
     * @param city The code of the city.
     * @return A pair containing the city code and its maximum flow.
     */
    std::pair<std::string, double> getMaxFlowInCity(const std::string& city);

    /**
     * @brief Retrieves the network flow.
     *
     * Obtains the flow values for cities within the network.
     * It first verifies the validity of the maximum flow values using edmondsKarp if necessary.
     * Then, it retrieves the super sink vertex. It iterates over incoming pipes to the super sink, collecting flow
     * values for cities and storing them in an unordered map.
     *
     * @return An unordered map containing vertex codes and their respective flow values.
     */
    std::unordered_map<std::string, double> getNetworkFlow();

    // For T3.1
    /**
     * @brief Retrieves vertices affected by a reservoir.
     *
     * Analyzes the impact of removing a reservoir on city flows.
     * It locates the reservoir in the network and retrieves the initial flow values before removal.
     * Then, it sets the reservoir's outgoing pipes' capacities to 0, recalculates the flows, and compares the before-and-after values.
     *
     * @param res_id The identifier of the reservoir.
     * @return An unordered map containing vertex codes and their respective minimum and maximum flow values.
     */
    std::unordered_map<std::string, std::pair<double, double>> getAffectedByReservoir( const std::string& res_id);

    /**
     * @brief Retrieves vertices affected by a pumping station.
     *
     * Examines the impact of removing a pumping station on city flows.
     * It first locates the station in the network and retrieves the initial flow values before removal.
     * Then, it temporarily removes the station's incoming and outgoing pipes, recalculates the flows, and compares the before-and-after values.
     *
     * @param res_id The identifier of the pumping station.
     * @return An unordered map containing vertex codes and their respective minimum and maximum flow values.
     */
    std::unordered_map<std::string, std::pair<double, double>> getAffectedByStation( const std::string& res_id);

    void balanceNetwork();

};

#endif //DA_PROJECT_23_24_NETWORKCONTROLLER_H
