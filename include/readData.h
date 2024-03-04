//
// Created by david on 02-03-2024.
//

#ifndef DA_PROJECT_23_24_READDATA_H
#define DA_PROJECT_23_24_READDATA_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include "../Code/Reservoir.h"
#include "../Code/Station.h"
#include "../Code/City.h"
#include "../Code/ServicePoint.h"
#include "../data_structures/Graph.h"

using namespace std;

class readData {
public:
    unordered_map<string, ServicePoint*> servicePoints;
    unordered_set<string> reservoirs;
    unordered_set<string> stations;
    unordered_map<string, string> pipes;
    unordered_set<string> cities;

    Graph<ServicePoint*> bigGraph;

    void readReservoirs();
    void readStations();
    void readPipes();
    void readCities();
};


#endif //DA_PROJECT_23_24_READDATA_H
