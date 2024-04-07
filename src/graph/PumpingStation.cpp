#include "PumpingStation.h"


PumpingStation::PumpingStation(const std::string& id, unsigned  int psID) : Vertex(id) {
    this->stationId = psID;
}

VertexType PumpingStation::getType() const {
    return VertexType::PumpingStationVertex;
}
