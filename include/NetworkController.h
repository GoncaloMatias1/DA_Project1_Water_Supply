//
// Created by admin1 on 08-03-2024.
//

#ifndef DA_PROJECT_23_24_NETWORKCONTROLLER_H
#define DA_PROJECT_23_24_NETWORKCONTROLLER_H

#include "Graph.h"
#include <fstream>
#include <sstream>
#include <iostream>


class NetworkController{
private:
    Graph network;
    std::string dataRoot;
public:
    NetworkController(const std::string& src);
    void parseData();

    void readReservoirs();
    void readPumpingStations();
    void readCities();
    void readPipes();


};

#endif //DA_PROJECT_23_24_NETWORKCONTROLLER_H
