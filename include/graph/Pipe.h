#ifndef DA_PROJECT_23_24_PIPE_H
#define DA_PROJECT_23_24_PIPE_H

#include "Graph.h"
#include <string>
#include "Vertex.h"
class Vertex;

/**
 * @class Pipe
 * @brief Represents a pipe connecting two vertices in a graph.
 */
class Pipe{
private:
    double capacity; /**< Maximum capacity of the pipe */
    // Used for network improvements
    double originalCapacity; /**< Original capacity of the pipe */
    double flow; /**< Current flow through the pipe */
    Vertex* destination; /**< Destination vertex of the pipe */
    Vertex* origin; /**< Origin vertex of the pipe */
public:
    /**
     * @brief Constructor for Pipe class.
     *
     * Initializes a pipe object with the provided parameters.
     * It sets the maximum capacity of the pipe, its original capacity, the origin vertex, the destination vertex, and initializes the flow through the pipe to zero.
     *
     * @param maxCapacity Maximum capacity of the pipe.
     * @param origin The origin vertex of the pipe.
     * @param endpoint The destination vertex of the pipe.
     */
    Pipe(double maxCapacity, Vertex* origin,Vertex* endpoint);

    // Class getters
    /**
     * @brief Retrieves the maximum capacity of the pipe.
     *
     * Retrieves the maximum capacity of the pipe and returns it as a double value.
     *
     * @return The maximum capacity of the pipe.
     */
    double getCapacity() const;

    /**
     * @brief Retrieves the destination vertex of the pipe.
     *
     * Returns a pointer to the endpoint vertex of the pipe.
     *
     * @return A pointer to the destination vertex.
     */
    Vertex* getDestination() const;

    /**
     * @brief Retrieves the identifier of the destination vertex.
     *
     * Returns a constant reference to the code of the endpoint vertex of the pipe.
     *
     * @return A constant reference to the identifier of the destination vertex.
     */
    const std::string& getDestinationId() const;

    /**
     * @brief Retrieves the current flow through the pipe.
     *
     * Returns the current flow value through the pipe.
     *
     * @return The current flow through the pipe.
     */
    double getFlow() const;

    /**
     * @brief Retrieves the origin vertex of the pipe.
     *
     * Returns a pointer to the vertex from which the pipe originates.
     *
     * @return A pointer to the origin vertex.
     */
    Vertex* getOrigin();


    /**
     * @brief Retrieves the original capacity of the pipe.
     *
     * Returns the original maximum capacity of the pipe before any modifications.
     *
     * @return The original capacity of the pipe.
     */
    double getOriginalCapacity();

    // Class setters

    /**
     * @brief Sets the maximum capacity of the pipe.
     *
     * Sets the new capacity of the pipe to the specified value.
     *
     * @param newCapacity The new maximum capacity of the pipe.
     */
    void setCapacity(double newCapacity);

    /**
     * @brief Sets the destination vertex of the pipe.
     *
     * Sets the destination vertex of the pipe to the specified vertex.
     *
     * @param destination A pointer to the destination vertex.
     */
    void setDestination(Vertex* destination);

    /**
     * @brief Sets the current flow through the pipe.
     *
     * Sets the flow rate of the pipe to the specified value.
     *
     * @param newFlow The new flow through the pipe.
     */
    void setFlow(double newFlow);

    /**
     * @brief Sets the origin vertex of the pipe.
     *
     * Sets the origin vertex of the pipe to the specified vertex.
     *
     * @param orig A pointer to the origin vertex.
     */
    void setOrigin(Vertex* orig);

    /**
     * @brief Retrieves the identifier of the pipe.
     *
     * Returns a unique identifier for the pipe, which is a combination of the origin vertex code and the destination vertex code, separated by a hyphen.
     *
     * @return A string referring to the ID of the pipe.
     */
    std::string getPipeId() const;



};

#endif //DA_PROJECT_23_24_PIPE_H
