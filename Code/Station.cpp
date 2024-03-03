#include "Station.h"

Station::Station(float id, string& code){
    this->id = id;
    this->code = code;
}

float Station::getId() const{
    return id;
}

string Station::getCode() const{
    return code;
}

bool Station::operator==(const Station &other) const {
    return id == other.id && code == other.code;
}