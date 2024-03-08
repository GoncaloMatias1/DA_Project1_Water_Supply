//
// Created by admin1 on 08-03-2024.
//

#include "NetworkController.h"
#include "City.h"
#include "WaterReservoir.h"
#include "PumpingStation.h"


NetworkController::NetworkController(const std::string &src) {
    this->dataRoot = src;
    this->parseData();
}

void NetworkController::parseData() {
    try{
        this->readCities();
        this->readReservoirs();
        this->readPumpingStations();
        this->readPipes();
        std::cout << "Data Parsing Complete...\n";
    } catch(const std::exception& e){
        std::cerr << "ERROR IN DATA PARSING: "<<  e.what() << std::endl;
    }

}

void NetworkController::readCities() {
    std::ifstream file(this->dataRoot + "/Cities.csv");
    if(!file.is_open()){
        throw std::invalid_argument("Couldn't open cities file!");
    }

    std::string line; getline(file, line);

    while(getline(file, line)) {

        std::istringstream iss(line);

        std::string city,id,code,demand,population;
        getline(iss, city, ',');
        getline(iss, id, ',');
        getline(iss, code, ',');
        getline(iss, demand, ',');
        getline(iss, population, '\r');


        unsigned int id_ = std::stoul(id);
        double demand_ = std::stod(demand);
        unsigned int population_ = std::stoul(population);

        City* city_ = new City(code, city, id_, demand_, population_);

        this->network.addVertex(city_);
    }
}

void NetworkController::readPumpingStations() {
    std::ifstream file(this->dataRoot + "/Stations.csv");
    if(!file.is_open()){
        throw std::invalid_argument("Couldn't open stations file!");
    }

    std::string line; getline(file, line);

    while(getline(file, line)) {
        std::istringstream iss(line);

        std::string id, code;
        getline(iss, id, ',');
        getline(iss, code, '\r');

        unsigned int id_ = stoul(id);

        PumpingStation* station = new PumpingStation(code, id_);
        this->network.addVertex(station);
    }
}


void NetworkController::readReservoirs() {
    std::ifstream file(this->dataRoot + "/Reservoir.csv");
    if(!file.is_open()){
        throw std::invalid_argument("Couldn't open Reservoir file!");
    }

    std::string line; getline(file, line);

    while(getline(file, line)) {
        std::istringstream iss(line);

        std::string res, mun, id, code, max_dev;
        getline(iss, res, ',');
        getline(iss, mun, ',');
        getline(iss, id, ',');
        getline(iss, code, ',');
        getline(iss, max_dev, '\r');

        unsigned  int id_ = std::stoul(id);
        double maxDelivery = std::stod(max_dev);

        WaterReservoir* reservoir = new WaterReservoir(code, res, mun, id_, maxDelivery);
        this->network.addVertex(reservoir);
    }
}

void NetworkController::readPipes() {
    std::ifstream file(this->dataRoot + "/Pipes.csv");
    if(!file.is_open()){
        throw std::invalid_argument("Couldn't open pipes file!");
    }

    std::string line; getline(file, line);

    while (getline(file, line)) {

        std::istringstream iss(line);

        std::string Service_Point_A, Service_Point_B, Capacity, Direction;
        getline(iss, Service_Point_A, ',');
        getline(iss, Service_Point_B, ',');
        getline(iss, Capacity, ',');
        getline(iss, Direction, '\r');

        double cap = std::stod(Capacity);

        if((this->network.findVertex(Service_Point_A) == nullptr) || (this->network.findVertex(Service_Point_B) == nullptr)){
            throw std::invalid_argument("One of the endpoints does not exist in the network!");
        }

        this->network.addEdge(Service_Point_A, Service_Point_B, cap);
        if(Direction == "0"){
            this->network.addEdge(Service_Point_B, Service_Point_A, cap);
        }
    }
}
