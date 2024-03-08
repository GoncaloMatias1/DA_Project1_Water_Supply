//
// Created by admin1 on 08-03-2024.
//

#ifndef DA_PROJECT_23_24_PUMPINGSTATION_H
#define DA_PROJECT_23_24_PUMPINGSTATION_H

#include "Vertex.h"

class PumpingStation : public Vertex{
private:
    unsigned int stationId;
public:
    PumpingStation(const std::string& id, unsigned  int psID);

};

#endif //DA_PROJECT_23_24_PUMPINGSTATION_H
