//
// Created by admin1 on 03-03-2024.
//

#ifndef DA_PROJECT_23_24_VERTEX_H
#define DA_PROJECT_23_24_VERTEX_H

#include "Pipe.h"
#include <vector>
#include <string>

enum VertexType{
        ReservoirVertex,
        PumpingStationVertex,
        CityVertex,
        VirtualVertex
};

class Pipe;
class Vertex{
protected:
    std::vector<Pipe*> outgoing;
    std::vector<Pipe*> incoming;
    std::string code;
    bool visited = false;

    bool processing = false;
    double dist = 0;
    Pipe *path = nullptr;

public:
    Vertex(const std::string&);
    void clearIncoming();

    // Class setters
    void setCode(const std::string& identifier);
    void setOutgoing(const std::vector<Pipe*>& newAdj);
    void setIncoming(const std::vector<Pipe*>& newAdj);

    void setVisited(bool newSt);
    void setProcessing(bool proc);
    void setPath(Pipe* parent);

    void addOutgoingPipe(Pipe* newPipe);
    void addIncomingPipe(Pipe* newPipe);

    bool removePipeTo(const std::string& endpoint);
    bool removePipeFrom(const std::string& origin);


    // Class getters
    const std::string& getCode() const;
    bool isVisited() const;
    bool isProcessing() const;
    Pipe* getPath() const;
    std::vector<Pipe*> getIncoming() const;
    std::vector<Pipe*> getOutgoing() const;

    virtual VertexType getType() const;
};

#endif //DA_PROJECT_23_24_VERTEX_H
