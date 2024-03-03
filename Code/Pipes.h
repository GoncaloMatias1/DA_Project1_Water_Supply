#include <string>

using namespace std;

#ifndef DA_PROJECT_23_24_PIPES_H
#define DA_PROJECT_23_24_PIPES_H


class Pipes {
public:
    Pipes() = default;
    Pipes(string& SP_A, string& SP_B, float capacity, float direction);
    string getSP_A() const;
    string getSP_B() const;
    float getCapacity() const;
    float getDirection() const;
private:
    string SP_A;
    string SP_B;
    float capacity;
    float direction;
};


#endif //DA_PROJECT_23_24_PIPES_H
