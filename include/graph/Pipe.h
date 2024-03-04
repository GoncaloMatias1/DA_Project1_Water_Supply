//
// Created by admin1 on 03-03-2024.
//

#ifndef DA_PROJECT_23_24_PIPE_H
#define DA_PROJECT_23_24_PIPE_H

#include "Graph.h"

class Pipe{
private:
    float capacity;
    Vertex* destination;
public:
    Pipe();

    // Class getters
    float getCapacity() const;
    Vertex* getDestination() const;

    // Class setters
    void setCapacity(float newCapacity);
    void setDestination(Vertex* destination);


};

#endif //DA_PROJECT_23_24_PIPE_H
