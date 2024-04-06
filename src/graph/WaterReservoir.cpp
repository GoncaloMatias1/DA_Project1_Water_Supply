//
// Created by admin1 on 08-03-2024.
//
#include "WaterReservoir.h"


WaterReservoir::WaterReservoir(const std::string &id, const std::string &name_, const std::string &municipality_,unsigned int resID, double maxDel) : Vertex(id){
    this->name = name_;
    this->municipality = municipality_;
    this->reservoirID = resID;
    this->maxDelivery = maxDel;
}

VertexType WaterReservoir::getType() const {
    return VertexType::ReservoirVertex;
}

double WaterReservoir::getMaxDelivery() const {
    return this->maxDelivery;
}


