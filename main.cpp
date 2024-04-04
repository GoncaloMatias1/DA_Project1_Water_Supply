#include <iostream>
#include "NetworkController.h"
#include "Menu.h"
int main() {
    NetworkController controller("../data");
    char choice;
    while(! ((choice - '0') == 1 || (choice - '0') == 2)){
        std::cout << "Choose a dataset:" << std::endl;
        std::cout << "1. Madeira (small)" << std::endl;
        std::cout << "2. Continental Portugal (big)" << std::endl;
        std::cout << "Enter your choice (1 or 2): ";
        std::cin >> choice;

        switch (choice - '0') {
            case 1:
                controller.initializeNetwork(true);
                break;
            case 2:
                controller.initializeNetwork(false);
                break;
        }
    }
    
    Menu menu(&controller);
    return 0;
}
