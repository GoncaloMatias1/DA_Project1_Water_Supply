#include <iostream>
#include "NetworkController.h"

void showMenu() {
    std::cout << "\n=== Water Supply Management Analysis System Menu ===\n";
    std::cout << "1. Initialize Network and Run Edmonds-Karp Algorithm\n";
    std::cout << "2. Exit\n";
    std::cout << "Select an option: ";
}

int main() {
    NetworkController controller("../data"); // Controller is created, but not initialized yet

    bool running = true;
    int choice;

    while (running) {
        showMenu();
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear(); // Clear the error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the input
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1:
                controller.initializeNetwork(); // Now initialization is controlled by the menu
                break;
            case 2:
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
