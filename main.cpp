#include <iostream>
#include "NetworkController.h"
#include "Menu.h"

void showMenu() {
    std::cout << "\n=== Water Supply Management Analysis System Menu ===\n";
    std::cout << "1. Calculate Max flow of network\n";
    std::cout << "2. Calculate Max Flow to a City\n";
    std::cout << "3. Calculate Cities with deficit of water\n";
    std::cout << "4. Get statistics on reservoir removal\n";
    std::cout << "5. Exit\n";
    std::cout << "Select an option: ";
}

int main() {
    NetworkController controller("../data");
    controller.initializeNetwork(true);
    Menu menu(&controller);
    return 0;
}
