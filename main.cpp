#include <iostream>
#include "NetworkController.h"

void showMenu() {
    std::cout << "\n=== Water Supply Management Analysis System Menu ===\n";
    std::cout << "1. Initialize Network and Run Edmonds-Karp Algorithm\n";
    std::cout << "2. Calculate Max Flow to a City\n";
    std::cout << "3. Exit\n";
    std::cout << "Select an option: ";
}

int main() {
    NetworkController controller("../data");
    std::string cityCode;
    bool running = true;
    int choice;

    while (running) {
        showMenu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                controller.initializeNetwork();
                break;
            case 2:
                std::cout << "Enter the city code to calculate the max flow to: ";
                std::cin >> cityCode;
                controller.edmondsKarpForCity(cityCode);
                break;
            case 3:
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
