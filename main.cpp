#include <iostream>
#include "NetworkController.h"

void showMenu() {
    std::cout << "\n=== Water Supply Management Analysis System Menu ===\n";
    std::cout << "1. Calculate Max flow of network\n";
    std::cout << "2. Calculate Max Flow to a City\n";
    std::cout << "3. Calculate Cities with deficit of water\n";
    std::cout << "4. Exit\n";
    std::cout << "Select an option: ";
}

int main() {
    NetworkController controller("../data");
    controller.initializeNetwork();
    std::string cityCode;
    std::vector<std::pair<std::string, double>> pairCityFlowVector;
    std::pair<std::string, double> pairCityFlow;
    double totalNetworkFlow = 0;
    bool running = true;
    int choice;

    while (running) {
        showMenu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                pairCityFlowVector = controller.getNetworkFlow();
                std::cout << "CityCode, Flow" << std::endl;
                for(const std::pair<std::string, double>& pair: pairCityFlowVector){
                    totalNetworkFlow += pair.second;
                    std::cout << pair.first << ", " << pair.second << std::endl;
                }
                std::cout << "Total flow is " << totalNetworkFlow << std::endl;
                break;
            case 2:
                std::cout << "Enter the city code to calculate the max flow to: ";
                std::cin >> cityCode;
                pairCityFlow = controller.getMaxFlowInCity(cityCode);
                std::cout << "City " << pairCityFlow.first << " has a max flow of " << pairCityFlow.second << std::endl;
                break;
            case 3:
                std::cout << "CityCode, Deficit (m3)\n";
                pairCityFlowVector = controller.getLowWaterCities();
                for(const std::pair<std::string, double>& pair: pairCityFlowVector){
                    totalNetworkFlow += pair.second;
                    std::cout << pair.first << ", " << pair.second << std::endl;
                }
                break;

            case 4:
                std::cout << "Exiting program...\n";
                running = false;
                break;
            default:
                std::cout << "Invalid option. Please try again.\n";
                break;
        }
    }

    return 0;
}
