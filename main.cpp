#include <iostream>
#include "NetworkController.h"


int main() {
    NetworkController controller("../data");
    controller.edmondsKarp();
    for(auto pair : controller.getLowWaterCities()){
        std::cout << "City with code " << pair.first << " has a deficit of  " << pair.second << std::endl;
    }

    return 0 ;
}