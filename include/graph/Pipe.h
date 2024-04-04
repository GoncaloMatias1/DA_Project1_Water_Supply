//
// Created by admin1 on 03-03-2024.
//

#ifndef DA_PROJECT_23_24_PIPE_H
#define DA_PROJECT_23_24_PIPE_H

#include "Graph.h"
#include <string>
#include "Vertex.h"
class Vertex;

class Pipe{
private:
    double capacity;
    double flow;
    Vertex* destination;
    Vertex* origin;
public:
    Pipe(double maxCapacity, Vertex* origin,Vertex* endpoint);

    // Class getters
    double getCapacity() const;
    Vertex* getDestination() const;
    const std::string& getDestinationId() const;
    double getFlow() const;
    Vertex* getOrigin();

    // Class setters
    void setCapacity(double newCapacity);
    void setDestination(Vertex* destination);
    void setFlow(double newFlow);
    void setOrigin(Vertex* orig);
    std::string getPipeId() const;



};

#endif //DA_PROJECT_23_24_PIPE_H
