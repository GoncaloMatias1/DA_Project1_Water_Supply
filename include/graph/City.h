//
// Created by admin1 on 08-03-2024.
//

#ifndef DA_PROJECT_23_24_CITY_H
#define DA_PROJECT_23_24_CITY_H

#include "Vertex.h"

class City : public Vertex{
private:
    std::string cityName;
    unsigned int cityId;
    unsigned int pop;
    double demand;
public:
    City(const std::string& vertexId, const std::string &name, unsigned int id, double demand_, unsigned int population);

    // Getters and setters

};

#endif //DA_PROJECT_23_24_CITY_H
