//
// Created by admin1 on 03-03-2024.
//

#ifndef DA_PROJECT_23_24_VERTEX_H
#define DA_PROJECT_23_24_VERTEX_H

#include "Pipe.h"
#include <vector>
#include <string>

class Pipe;
class Vertex{
protected:
    std::vector<Pipe*> adj;
    std::string id;

public:
    Vertex(const std::string&);

    // Class setters
    void setID(const std::string& identifier);

    void setAdj(const std::vector<Pipe*>& newAdj);

    void addPipe(Pipe* newPipe);

    bool removePipeTo(const std::string& endpoint);


    // Class getters
    const std::string& getID() const;


};

#endif //DA_PROJECT_23_24_VERTEX_H
