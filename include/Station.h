#include <string>
#include "ServicePoint.h"

using namespace std;

#ifndef DA_PROJECT_23_24_STATION_H
#define DA_PROJECT_23_24_STATION_H

class Station : public ServicePoint {
public:
    Station() = default;
    Station(float id, string& code);
    float getId() const;
    string getCode() const;
    bool operator==(const Station &other) const;
private:
    float id;
    string code;
};


#endif //DA_PROJECT_23_24_STATION_H
