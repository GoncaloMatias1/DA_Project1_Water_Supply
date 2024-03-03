#include "readData.h"


void readData::readReservoirs(){
    ifstream file("../Project1DataSetSmall/Reservoirs_Madeira.csv");
    if(!file.is_open()){
        cout << "Impossible to open the file!" << endl;
    }

    string line; getline(file, line);

    while(getline(file, line)) {
        istringstream iss(line);

        vector<string> tokens;
        string token;
        while(getline(iss, token, ',')) {
            tokens.push_back(token);
        }

        if(tokens.size() < 5 || (tokens[0].empty() && tokens[1].empty() && tokens[2].empty() && tokens[3].empty() && tokens[4].empty())) continue;

        string res = tokens[0];
        string mun = tokens[1];
        string id = tokens[2];
        string code = tokens[3];
        string max_dev = tokens[4];

        float id_ = stof(id);

        Reservoir* reservoir = new Reservoir(res, mun, id_, code, max_dev);
        servicePoints[code] = reservoir;

        reservoirs.insert(code);
        bigGraph.addVertex(reservoir);
    }
}

void readData::readStations(){
    ifstream file("../Project1DataSetSmall/Stations_Madeira.csv");
    if(!file.is_open()){
        cout << "Impossible to open the file!" << endl;
        return;
    }

    string line; getline(file, line);

    while(getline(file, line)) {
        istringstream iss(line);

        vector<string> tokens;
        string token;
        while(getline(iss, token, ',')) {
            tokens.push_back(token);
        }

        if(tokens.size() < 2 || (tokens[0].empty() && tokens[1].empty())) continue;

        string id = tokens[0];
        string code = tokens[1];

        float id_ = stof(id);

        Station* station = new Station(id_, code);
        servicePoints[code] = station;

        stations.insert(code);
        bigGraph.addVertex(station);
    }
}

void readData::readCities(){
    ifstream file("../Project1DataSetSmall/Cities_Madeira.csv");
    if(!file.is_open()){
        cout << "Impossible to open the file!" << endl;
        return;
    }

    string line; getline(file, line);

    while(getline(file, line)) {

        istringstream iss(line);

        string city,id,code,demand,population;
        getline(iss, city, ',');
        getline(iss, id, ',');
        getline(iss, code, ',');
        getline(iss, demand, ',');
        getline(iss, population, '\r');

        population.erase(remove(population.begin(), population.end(), '\"'), population.end());
        population.erase(remove(population.begin(), population.end(), ','), population.end());

        float id_ = stof(id);
        float demand_ = stof(demand);
        float population_ = stof(population);

        City* city_ = new City(city, id_, code, demand_, population_);
        servicePoints[code] = city_;

        cities.insert(code);
        bigGraph.addVertex(city_);
    }
}

void readData::readPipes() {
    ifstream file("../Project1DataSetSmall/Pipes_Madeira.csv");
    if(!file.is_open()){
        cout << "Impossible to open the file!" << endl;
        return;
    }

    string line; getline(file, line);

    while (getline(file, line)) {

        istringstream iss(line);

        string Service_Point_A, Service_Point_B, Capacity, Direction;
        getline(iss, Service_Point_A, ',');
        getline(iss, Service_Point_B, ',');
        getline(iss, Capacity, ',');
        getline(iss, Direction, '\r');

        pipes.insert(make_pair(Service_Point_A, Service_Point_B));
        bigGraph.addEdge(servicePoints[Service_Point_A], servicePoints[Service_Point_B], stof(Capacity)); //TODO NÃO CONSEGUI ADICIONAR A COMPONENTE DIRECTION!
    }
}