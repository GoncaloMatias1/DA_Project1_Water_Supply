//
// Created by admin1 on 03-04-2024.
//

#ifndef DA_PROJECT_23_24_MENU_H
#define DA_PROJECT_23_24_MENU_H

#include "NetworkController.h"
#include <cstdlib>

class Menu{
private:
    NetworkController* controller;
    bool running = true;
public:
    Menu(NetworkController* control);

    // input handling
    static std::string getInput(const std::string& out);
    void waitForContinue();
    void clearTerminal();

    // Main menu
    void showMainMenu();
    void run_menu();

    // T2.1 Menu
    void showMaxFlowResult();
    void showMaxFlowToCity();
    // T2.2 Menu
    void showCitiesWithDeficit();
    void displayCityInfo(const std::string& code,const std::string& cityName, int demand, int actualFlow, int deficit);
    // T3.1 Menu
    void showReservoirRemoval();
    // T3.2 Menu
    void showStationRemoval();

};

#endif //DA_PROJECT_23_24_MENU_H
