#include <string>
#include "ServicePoint.h"

#ifndef DA_PROJECT_23_24_CITY_H
#define DA_PROJECT_23_24_CITY_H


class City : public ServicePoint {
public:
    City() = default;
    City(string& city, float id, string& code, float demand, float population);
    string getCity() const;
    float getId() const;
    string getCode() const;
    float getDemand() const;
    float getPopulation() const;
    bool operator==(const City &other) const;
private:
    string city;
    float id;
    string code;
    float demand;
    float population;
};


#endif //DA_PROJECT_23_24_CITY_H
