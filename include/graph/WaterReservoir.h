//
// Created by admin1 on 08-03-2024.
//

#ifndef DA_PROJECT_23_24_WATERRESERVOIR_H
#define DA_PROJECT_23_24_WATERRESERVOIR_H

#include "Vertex.h"

class WaterReservoir : public Vertex{
private:
    std::string name;
    std::string municipality;
    unsigned int reservoirID;
    double maxDelivery;
public:
    WaterReservoir(const std::string& id, const std::string& name, const std::string& municipality, unsigned int resID, double maxDel);

    VertexType getType() const override;
    double getMaxDelivery() const;
};

#endif //DA_PROJECT_23_24_WATERRESERVOIR_H
