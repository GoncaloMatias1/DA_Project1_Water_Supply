#include "City.h"

City::City(string& city, float id, string& code, float demand, float population){
    this->city = city;
    this->id = id;
    this->code = code;
    this->demand = demand;
    this->population = population;
}

string City::getCity() const{
    return city;
}

float City::getId() const{
    return id;
}

string City::getCode() const{
    return code;
}

float City::getDemand() const{
    return demand;
}

float City::getPopulation() const{
    return population;
}

bool City::operator==(const City &other) const {
    return id == other.id && code == other.code;
}
