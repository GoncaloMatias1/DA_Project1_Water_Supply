#include "Pipes.h"

Pipes::Pipes(string& SP_A, string& SP_B, float capacity, float direction){
    this->SP_A = SP_A;
    this->SP_B = SP_B;
    this->capacity = capacity;
    this->direction = direction;
}

string Pipes::getSP_A() const{
    return SP_A;
}

string Pipes::getSP_B() const{
    return SP_B;
}

float Pipes::getCapacity() const{
    return capacity;
}

float Pipes::getDirection() const{
    return direction;
}