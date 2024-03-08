//
// Created by admin1 on 03-03-2024.
//

#ifndef DA_PROJECT_23_24_PIPE_H
#define DA_PROJECT_23_24_PIPE_H

#include "Graph.h"
#include <string>
class Vertex;

class Pipe{
private:
    double capacity;
    Vertex* destination;
public:
    Pipe(float maxCapacity, Vertex* endpoint);

    // Class getters
    double getCapacity() const;
    Vertex* getDestination() const;
    const std::string& getDestinationId() const;

    // Class setters
    void setCapacity(double newCapacity);
    void setDestination(Vertex* destination);


};

#endif //DA_PROJECT_23_24_PIPE_H
