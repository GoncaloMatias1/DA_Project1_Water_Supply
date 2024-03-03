#include "Reservoir.h"

Reservoir::Reservoir(string& res, string& mun, float id, string& code, string& max_dev){
    this->res = res;
    this->mun = mun;
    this->id = id;
    this->code = code;
    this->max_dev = max_dev;
}

string Reservoir::getReservoir() const{
    return code;
}

string Reservoir::getMunicipality() const{
    return mun;
}

float Reservoir::getId() const{
    return id;
}

string Reservoir::getCode() const{
    return code;
}

string Reservoir::getMaximumDelivery() const{
    return code;
}

bool Reservoir::operator==(const Reservoir &other) const {
    return id == other.id && code == other.code;
}
