//
// Created by admin1 on 08-03-2024.
//

#include <queue>
#include "NetworkController.h"
#include "City.h"
#include "WaterReservoir.h"
#include "PumpingStation.h"


NetworkController::NetworkController(const std::string &src) {
    this->dataRoot = src;
}

void NetworkController::initializeNetwork() {
    this->parseData();
    std::cout << this->network.getCityId("Beja") << std::endl;
    this->edmondsKarp();
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

Vertex* NetworkController::generateSuperSource() {
    // Create super source with code "SuperSource"
    Vertex* super = this->network.findVertex("SuperSource");
    if(super!= nullptr) return super;

    super = new Vertex("SuperSource");
    this->network.addVertex(super);

    // Connect super source to all reservoirs
    for(Vertex* vertex: this->network.getVertexSet()){

        WaterReservoir* reservoir = dynamic_cast<WaterReservoir*>(vertex);
        if(reservoir != nullptr){
            // Found a reservoir
            Pipe* pipe = new Pipe(reservoir->getMaxDelivery(), super, vertex);
            super->addOutgoingPipe(pipe);
            vertex->addIncomingPipe(pipe);
        }
    }
    return super;
}

Vertex* NetworkController::generateSuperSink() {
    // Create super sink with code "SuperSink"
    Vertex* super = this->network.findVertex("SuperSink");
    if(super!= nullptr) return super;

    super = new Vertex("SuperSink");
    this->network.addVertex(super);

    // generate pipes to super sink from cities
    for(Vertex* vertex: this->network.getVertexSet()){

        City* city = dynamic_cast<City*>(vertex);
        if(city != nullptr){
            // Found a city
            Pipe* pipe =new Pipe(INF, city, super);
            city->addOutgoingPipe(pipe);
            super->addIncomingPipe(pipe);
        }
    }
    return super;
}

void NetworkController::edmondsKarp() {
    Vertex* source = this->generateSuperSource();
    Vertex* sink = this->generateSuperSink();

    for(Vertex* vertex: this->network.getVertexSet()){
        for(Pipe* pipe: vertex->getOugoing()){
            pipe->setFlow(0);
        }
    }

    while(this->findAugmentingPath(source, sink)){
        double f = this->findMinResidualAlongPath(source, sink);
        this->augmentFlowAlongPath(source, sink , f);
    }

    double maxFlow = 0;
    for(Pipe* pipe: sink->getIncoming()){
        maxFlow += pipe->getFlow();
    }
    std::cout << "Max flow is " << maxFlow << std::endl;
}

bool NetworkController::findAugmentingPath(Vertex *source, Vertex *sink) {
    for(Vertex* v: this->network.getVertexSet()){
        v->setVisited(false);
    }

    source->setVisited(true);
    std::queue<Vertex*> q;
    q.push(source);

    while(!q.empty() && !sink->isVisited()){
        Vertex* v = q.front();
        q.pop();

        for(Pipe* pipe: v->getOugoing()){
            testAndVisit(q, pipe, pipe->getDestination(), pipe->getCapacity() - pipe->getFlow());
        }

        for(Pipe* pipe: v->getIncoming()){
            testAndVisit(q, pipe, pipe->getOrigin(), pipe->getFlow());
        }
    }

    return sink->isVisited();
}

void NetworkController::testAndVisit(std::queue<Vertex *> &q, Pipe *pipe, Vertex *dest, double residual) {
    if(!dest->isVisited() && residual > 0){
        dest->setVisited(true);
        dest->setPath(pipe);
        q.push(dest);
    }
}

double NetworkController::findMinResidualAlongPath(Vertex *source, Vertex *sink) {
    double f = INF;

    for (Vertex* vertex = sink; vertex != source; ) {
        Pipe* pipe = vertex->getPath();
        if (pipe->getDestination() == vertex) {
            f = std::min(f, pipe->getCapacity() - pipe->getFlow());
            vertex = pipe->getOrigin();
        }
        else {
            f = std::min(f, pipe->getFlow());
            vertex = pipe->getDestination();
        }
    }

    return f;
}

void NetworkController::augmentFlowAlongPath(Vertex *source, Vertex *sink, double f) {
    for (Vertex* vertex = sink; vertex != source; ) {
        Pipe* pipe = vertex->getPath();
        double flow = pipe->getFlow();

        if (pipe->getDestination() == vertex) {
            pipe->setFlow(flow + f);
            vertex = pipe->getOrigin();
        }
        else {
            pipe->setFlow(flow - f);
            vertex = pipe->getDestination();
        }
    }
}


void NetworkController::edmondsKarpForCity(const std::string& cityCode) {
    // Initialize the super source and super sink
    Vertex* superSource = this->generateSuperSource();
    Vertex* originalSuperSink = this->generateSuperSink();

    // Redirect super sink connections temporarily to target city
    for (auto& pipe : originalSuperSink->getIncoming()) {
        Vertex* sourceVertex = pipe->getOrigin();
        this->network.addEdge(sourceVertex->getCode(), cityCode, pipe->getCapacity());
    }
    this->network.removeVertex("SuperSink"); // Remove super sink temporarily

    // Run the Edmonds-Karp algorithm
    this->edmondsKarp();

    // Calculate the maximum flow to the specific city
    double maxFlowToCity = 0;
    Vertex* cityVertex = this->network.findVertex(cityCode);
    for (auto& pipe : cityVertex->getIncoming()) {
        maxFlowToCity += pipe->getFlow();
    }

    // Output the result to console
    std::cout << "Maximum flow to city " << cityCode << " is " << maxFlowToCity << std::endl;

    // Save the result to a file
    std::ofstream outFile("max_flow_to_city_results.txt", std::ios::app); // Open in append mode
    if (outFile.is_open()) {
        outFile << cityCode << ", " << maxFlowToCity << std::endl;
        outFile.close();
    } else {
        std::cerr << "Error opening the output file." << std::endl;
    }

    // Restore the original network configuration
    this->network.addVertex(originalSuperSink);
    for (auto& pipe : originalSuperSink->getIncoming()) {
        Vertex* sourceVertex = pipe->getOrigin();
        this->network.addEdge(sourceVertex->getCode(), "SuperSink", pipe->getCapacity());
    }
    // Remove temporary edges to the city
    cityVertex->clearIncoming();

    // Optionally, reset all flows in the network for a clean state if necessary
    // ResetFlows();
}

