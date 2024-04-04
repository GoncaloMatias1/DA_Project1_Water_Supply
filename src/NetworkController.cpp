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
    this->maxFlowValid = false;
}

void NetworkController::initializeNetwork(bool small) {
    if(small) this->parseDataSmall();
    else this->parseData();
    this->edmondsKarp();
    this->saveCityData();
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

Vertex* NetworkController::getSuperSource() {
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

Vertex* NetworkController::getSuperSink() {
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
            Pipe* pipe =new Pipe(city->getDemand(), city, super);
            city->addOutgoingPipe(pipe);
            super->addIncomingPipe(pipe);
        }
    }
    return super;
}

void NetworkController::edmondsKarp() {
    Vertex* source = this->getSuperSource();
    Vertex* sink = this->getSuperSink();

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

    this->maxFlowValid = true;
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

std::vector<std::pair<std::string, double>> NetworkController::getLowWaterCities() {
    std::vector<std::pair<std::string, double>> result;
    if(!this->maxFlowValid) this->edmondsKarp();

    Vertex* superSink = this->network.findVertex("SuperSink");
    if(superSink == nullptr) return {};

    for(Pipe* pipe: superSink->getIncoming()){
        City* city = dynamic_cast<City*>(pipe->getOrigin());
        if(city != nullptr){
            if(city->getDemand() > pipe->getFlow()){
                result.emplace_back(city->getCode(), city->getDemand() - pipe->getFlow());
            }
        }
    }
    return result;
}

void NetworkController::saveCityData() {
    Vertex* superSink = this->getSuperSink();

    std::ofstream outFile("../output/max_flow_network.txt");
    if (outFile.is_open()) {
        outFile << "CityCode, CityDemand, CityFlow" << std::endl;
        for(Pipe* pipe: superSink->getIncoming()){
            City* city = dynamic_cast<City*>(pipe->getOrigin());
            if(city != nullptr)
                outFile << city->getCode() << ", " << city->getDemand()  << ", " << pipe->getFlow() << std::endl;
        }
        outFile.close();
    } else {
        std::cerr << "Error opening the output file." << std::endl;
    }

}

std::pair<std::string, double> NetworkController::getMaxFlowInCity(const std::string &city) {
    if(!this->maxFlowValid) this->edmondsKarp();
    City* cityVertex = dynamic_cast<City*>(this->network.findVertex(city));
    if(cityVertex == nullptr) return {city, -1};

    for(Pipe* pipe: cityVertex->getOugoing()){
        if(pipe->getDestination() == this->getSuperSink()){
            return {city, pipe->getFlow()};
        }
    }
    return {};
}

std::unordered_map<std::string, double> NetworkController::getNetworkFlow() {
    std::unordered_map<std::string, double> result;
    if(!this->maxFlowValid) edmondsKarp();

    Vertex* superSink = this->getSuperSink();
    for(Pipe* pipe : superSink->getIncoming()){
        City* city = dynamic_cast<City*>(pipe->getOrigin());
        if(city == nullptr) continue;
        result[city->getCode()] = pipe->getFlow();
    }

    return result;
}

std::unordered_map<std::string, std::pair<double, double>> NetworkController::getAffectedByReservoir(const std::string &res_id) {
    Vertex* vertex = this->network.findVertex(res_id);
    if(vertex == nullptr) return {};

    std::unordered_map<std::string, double> flowBeforeRemoval = this->getNetworkFlow();
    std::unordered_map<std::string, double> flowAfterRemoval;

    std::unordered_map<std::string, std::pair<double, double>> result;

    // Set vertex to pass 0 flow, and run the function to get the cities that are low
    for(Pipe* out_pipe : this->getSuperSource()->getOugoing()){
        if(out_pipe->getDestination() == vertex){
            double prevCapacity = out_pipe->getCapacity();
            out_pipe->setCapacity(0);
            this->edmondsKarp();
            flowAfterRemoval = this->getNetworkFlow();
            out_pipe->setCapacity(prevCapacity);
            break;
        }
    }

    // Iterave other before and after to find the divergent ones
    for(std::pair<std::string, double> pair: flowBeforeRemoval){
        if(flowAfterRemoval[pair.first] != pair.second){
            result[pair.first] = std::make_pair(pair.second, flowAfterRemoval[pair.first]);
        }
    }

    this->maxFlowValid = false;
    return result;
}

void NetworkController::parseDataSmall() {
    try{
        this->readCitiesSmall();
        this->readReservoirsSmall();
        this->readStationsSmall();
        this->readPipesSmall();
        std::cout << "Data Parsing (small data) Complete...\n";
    } catch(const std::exception& e){
        std::cerr << "ERROR IN DATA PARSING: "<<  e.what() << std::endl;
    }
}


void NetworkController::readReservoirsSmall(){
    std::ifstream file("../data/small/Project1DataSetSmall/Reservoirs_Madeira.csv");
    if(!file.is_open()){
        std::cout << "Impossible to open the file!" << std::endl;
    }

    std::string line; getline(file, line);

    while(getline(file, line)) {
        std::istringstream iss(line);

        std::vector<std::string> tokens;
        std::string token;
        while(getline(iss, token, ',')) {
            tokens.push_back(token);
        }

        if(tokens.size() < 5 || (tokens[0].empty() && tokens[1].empty() && tokens[2].empty() && tokens[3].empty() && tokens[4].empty())) continue;

        std::string res = tokens[0];
        std::string mun = tokens[1];
        std::string id = tokens[2];
        std::string code = tokens[3];
        std::string max_dev = tokens[4];

        float id_ = stof(id);
        double max_dev_ = stod(max_dev);

        WaterReservoir* reservoir = new WaterReservoir(code, res, mun, id_, max_dev_);
        this->network.addVertex(reservoir);
    }
}

void NetworkController::readStationsSmall(){
    std::ifstream file("../data/small/Project1DataSetSmall/Stations_Madeira.csv");
    if(!file.is_open()){
        std::cout << "Impossible to open the file!" << std::endl;
        return;
    }

    std::string line; getline(file, line);

    while(getline(file, line)) {
        std::istringstream iss(line);

        std::vector<std::string> tokens;
        std::string token;
        while(getline(iss, token, ',')) {
            tokens.push_back(token);
        }

        if(tokens.size() < 2 || (tokens[0].empty() && tokens[1].empty())) continue;

        std::string id = tokens[0];
        std::string code = tokens[1];

        float id_ = stof(id);

        PumpingStation* station = new PumpingStation(code, id_);
        this->network.addVertex(station);

    }
}

void NetworkController::readCitiesSmall(){
    std::ifstream file("../data/small/Project1DataSetSmall/Cities_Madeira.csv");
    if(!file.is_open()){
        std::cout << "Impossible to open the file!" << std::endl;
        return;
    }

    std::string line; getline(file, line);

    while(getline(file, line)) {

        std::istringstream iss(line);

        std::string city,id,code,demand,population;
        std::string var;
        getline(iss, city, ',');
        getline(iss, id, ',');
        getline(iss, code, ',');
        getline(iss, demand, ',');
        getline(iss, population, '\r');
        population.erase(population.begin());
        population.erase(population.end( ) - 1);



        unsigned int id_ = stoul(id);
        double demand_ = stof(demand);
        unsigned int population_ = stoul(population);

        City* city_ = new City(code, city, id_, demand_, population_);

        this->network.addVertex(city_);

    }
}

void NetworkController::readPipesSmall() {
    std::ifstream file("../data/small/Project1DataSetSmall/Pipes_Madeira.csv");
    if(!file.is_open()){
        std::cout << "Impossible to open the file!" << std::endl;
        return;
    }

    std::string line; getline(file, line);

    while (getline(file, line)) {

        std::istringstream iss(line);

        std::string Service_Point_A, Service_Point_B, Capacity, Direction;
        getline(iss, Service_Point_A, ',');
        getline(iss, Service_Point_B, ',');
        getline(iss, Capacity, ',');
        getline(iss, Direction, '\r');


        if((this->network.findVertex(Service_Point_A) == nullptr) || (this->network.findVertex(Service_Point_B) == nullptr)){
            throw std::invalid_argument("One of the endpoints does not exist in the network!");
        }

        double cap = std::stod(Capacity);

        this->network.addEdge(Service_Point_A, Service_Point_B, cap);

        if(Direction == "0"){
            this->network.addEdge(Service_Point_B, Service_Point_A, cap);
        }

    }
}

Vertex *NetworkController::getVertex(const std::string &id) {
    return this->network.findVertex(id);
}

std::unordered_map<std::string, std::pair<double, double>>
NetworkController::getAffectedByStation(const std::string &res_id) {
    Vertex* vertex = this->network.findVertex(res_id);
    if(vertex == nullptr) return {};

    std::unordered_map<std::string, double> flowBeforeRemoval = this->getNetworkFlow();
    std::unordered_map<std::string, double> flowAfterRemoval;

    std::unordered_map<std::string, std::pair<double, double>> result;

    std::vector<Pipe*> incoming = vertex->getIncoming();
    std::vector<Pipe*> outgoing = vertex->getOugoing();


    vertex->setIncoming({});
    vertex->setOutgoing({});
    this->edmondsKarp();
    flowAfterRemoval = this->getNetworkFlow();

    vertex->setOutgoing(outgoing);
    vertex->setIncoming(incoming);

    // Iterave other before and after to find the divergent ones
    for(std::pair<std::string, double> pair: flowBeforeRemoval){
        if(flowAfterRemoval[pair.first] != pair.second){
            result[pair.first] = std::make_pair(pair.second, flowAfterRemoval[pair.first]);
        }
    }

    this->maxFlowValid = false;
    return result;
}


