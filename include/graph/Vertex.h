//
// Created by admin1 on 03-03-2024.
//

#ifndef DA_PROJECT_23_24_VERTEX_H
#define DA_PROJECT_23_24_VERTEX_H

#include "Pipe.h"

class Vertex{
private:
    std::vector<Pipe*> adjPipes;
    std::vector<Pipe*> incomingPipes;

public:
    Vertex();

    // Class setters
    void setAdj(const std::vector<Pipe*>& newAdj);

    void addPipe(Pipe* newPipe);

    void addPipeTo(const std::string& endpoint, float capacity);
    void removePipeTo(const std::string& endpoint);

    void addIncomingPipeFrom();


    // Class getters

};

#endif //DA_PROJECT_23_24_VERTEX_H
