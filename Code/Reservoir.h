#include <string>
#include "ServicePoint.h"

using namespace std;

#ifndef DA_PROJECT_23_24_RESERVOIR_H
#define DA_PROJECT_23_24_RESERVOIR_H


class Reservoir : public ServicePoint {
public:
    Reservoir() = default;
    Reservoir(string& res, string& mun, float id, string& code, string& max_dev);
    string getReservoir() const;
    string getMunicipality() const;
    float getId() const;
    string getCode() const;
    string getMaximumDelivery() const;
    bool operator==(const Reservoir &other) const;
private:
    string res;
    string mun;
    float id;
    string code;
    string max_dev;
};


#endif //DA_PROJECT_23_24_RESERVOIR_H
