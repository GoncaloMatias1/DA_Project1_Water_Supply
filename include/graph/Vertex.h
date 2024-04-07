#ifndef DA_PROJECT_23_24_VERTEX_H
#define DA_PROJECT_23_24_VERTEX_H

#include "Pipe.h"
#include <vector>
#include <string>

/**
 * @class Vertex
 * @brief Represents all the existing vertices of a graph.
 */

/**
 * @enum VertexType
 * @brief Enumerates the types of vertices in the graph.
 */
enum VertexType{
        ReservoirVertex,
        PumpingStationVertex,
        CityVertex,
        VirtualVertex
};

class Pipe;
class Vertex{
protected:
    std::vector<Pipe*> outgoing; /**< Vector containing pointers to outgoing pipes */
    std::vector<Pipe*> incoming; /**< Vector containing pointers to incoming pipes */
    std::string code; /**< Identifier of the vertex */
    bool visited = false; /**< Flag indicating whether the vertex has been visited during traversal */

    bool processing = false; /**< Flag indicating whether the vertex is currently being processed */
    Pipe* path = nullptr; /**< Pointer to the predecessor pipe in the shortest path */

public:
    /**
     * @brief Constructor for Vertex class.
     *
     * The constructor of the Vertex class, which initializes a vertex object with a given identifier.
     * It sets the code of the vertex to the provided identifier and clears both the incoming and outgoing pipe lists associated with the vertex.
     *
     * @param identifier The identifier of the vertex.
     * @complexity O(1)
     */
    Vertex(const std::string& identifier);

    /**
     * @brief Clears the list of incoming pipes.
     *
     * Clears the list of incoming pipes associated with the vertex by removing all elements from the incoming vector.
     * @complexity O(1)
     */
    void clearIncoming();

    // Class setters

    /**
     * @brief Sets the identifier of the vertex.
     *
     * Sets the identifier (code) of the vertex to the provided string parameter.
     *
     * @param identifier The new identifier of the vertex.
     * @complexity O(1)
     */
    void setCode(const std::string& identifier);

    /**
     * @brief Sets the list of outgoing pipes.
     *
     * Sets the outgoing pipes of the vertex to the provided vector of Pipe pointers.
     *
     * @param newAdj The new list of outgoing pipes.
     * @complexity O(1)
     */
    void setOutgoing(const std::vector<Pipe*>& newAdj);

    /**
     * @brief Sets the list of incoming pipes.
     *
     * Sets the incoming pipes of the vertex to the provided vector of Pipe pointers.
     *
     * @param newAdj The new list of incoming pipes.
     * @complexity O(1)
     */
    void setIncoming(const std::vector<Pipe*>& newAdj);

    /**
     * @brief Sets the visited status of the vertex.
     *
     * Sets the visited status of the vertex to the provided boolean value.
     * If newSt is true, it means the vertex has been visited; otherwise, it has not been visited.
     *
     * @param newSt The new visited status of the vertex.
     * @complexity O(1)
     */
    void setVisited(bool newSt);

    /**
     * @brief Sets the processing status of the vertex.
     *
     * Sets the processing status of the vertex to the provided boolean value.
     * If proc is true, it means the vertex is being processed; otherwise, it is not being processed.
     *
     * @param proc The new processing status of the vertex.
     * @complexity O(1)
     */
    void setProcessing(bool proc);

    /**
     * @brief Sets the path (predecessor pipe) of the vertex.
     *
     * Sets the path of the vertex to the provided Pipe pointer.
     * This path typically represents the parent pipe through which this vertex was reached during graph traversal algorithms such as BFS or DFS.
     *
     * @param parent The new path (predecessor pipe) of the vertex.
     * @complexity O(1)
     */
    void setPath(Pipe* parent);

    /**
     * @brief Adds an outgoing pipe to the vertex.
     *
     * Adds a new outgoing pipe to the vertex's list of outgoing pipes.
     * It takes a pointer to a Pipe object as input and appends it to the outgoing vector of the vertex.
     *
     * @param newPipe The outgoing pipe to add.
     * @complexity O(1)
     */
    void addOutgoingPipe(Pipe* newPipe);

    /**
     * @brief Adds an incoming pipe to the vertex.
     *
     * Adds a new incoming pipe to the vertex's list of incoming pipes.
     * It takes a pointer to a Pipe object as input and appends it to the incoming vector of the vertex.
     *
     * @param newPipe The incoming pipe to add.
     * @complexity O(1)
     */
    void addIncomingPipe(Pipe* newPipe);

    /**
     * @brief Removes a pipe leading to the specified endpoint.
     * @param endpoint The identifier of the endpoint.
     * @return True if the pipe was successfully removed, false otherwise.
     * @complexity O(E) where E is the number of outgoing pipes.
     */
    bool removePipeTo(const std::string& endpoint);

    /**
     * @brief Removes a pipe originating from the specified origin.
     *
     * Removes a pipe that leads to a specified endpoint from the vertex's list of outgoing pipes.
     * It takes the endpoint's identifier as input and iterates through the outgoing vector of the vertex.
     * If a pipe with the specified destination endpoint is found, it removes that pipe from the outgoing vector and returns true.
     * If no such pipe is found, it returns false.
     *
     * @param origin The identifier of the origin.
     * @return True if the pipe was successfully removed, false otherwise.
     * @complexity O(E) where E is the number of incoming pipes.
     */
    bool removePipeFrom(const std::string& origin);


    // Class getters

    /**
     * @brief Retrieves the identifier of the vertex.
     *
     * Retrieves the code (identifier) of the vertex. It returns a constant reference to the code, ensuring that the code cannot be modified through this reference.
     *
     * @return The identifier of the vertex.
     * @complexity O(1)
     */
    const std::string& getCode() const;

    /**
     * @brief Checks if the vertex has been visited during traversal.
     *
     * Checks whether the vertex has been visited during a traversal or algorithm execution.
     * It returns a boolean value indicating whether the vertex has been visited (true) or not (false).
     *
     * @return True if the vertex has been visited, false otherwise.
     * @complexity O(1)
     */
    bool isVisited() const;

    /**
     * @brief Checks if the vertex is currently being processed.
     *
     * Checks whether the vertex is currently being processed during an algorithm execution.
     * It returns a boolean value indicating whether the vertex is being processed (true) or not (false).
     *
     * @return True if the vertex is being processed, false otherwise.
     * @complexity O(1)
     */
    bool isProcessing() const;

    /**
     * @brief Retrieves the predecessor pipe in the shortest path.
     *
     * Returns a pointer to the Pipe object representing the path leading to the current vertex during traversal or algorithm execution.
     * If no path has been set, it returns a null pointer.
     *
     * @return A pointer to the predecessor pipe.
     * @complexity O(1)
     */
    Pipe* getPath() const;

    /**
     * @brief Retrieves the list of incoming pipes.
     *
     * Returns a constant reference to the vector of pointers to incoming pipes connected to the current vertex.
     * This function allows access to the incoming pipes without modifying them.
     *
     * @return A vector containing pointers to incoming pipes.
     * @complexity O(1)
     */
    std::vector<Pipe*> getIncoming() const;

    /**
     * @brief Retrieves the list of outgoing pipes.
     *
     * Returns a constant reference to the vector of pointers to outgoing pipes connected to the current vertex.
     * This function allows access to the outgoing pipes without modifying them.
     *
     * @return A vector containing pointers to outgoing pipes.
     * @complexity O(1)
     */
    std::vector<Pipe*> getOutgoing() const;

    /**
     * @brief Retrieves the type of the vertex.
     *
     * In this implementation, it always returns VertexType::VirtualVertex, indicating that the vertex is a virtual vertex.
     *
     * @return The type of the vertex.
     * @complexity O(1)
     */
    virtual VertexType getType() const;
};

#endif //DA_PROJECT_23_24_VERTEX_H
