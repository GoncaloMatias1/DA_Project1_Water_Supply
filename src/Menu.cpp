//
// Created by admin1 on 03-04-2024.
//

#include <iomanip>
#include "Menu.h"
#include "City.h"
#include "PumpingStation.h"
#include "WaterReservoir.h"

#define GET_CITY_TEXT "Enter the city code to calculate the maximum flow: "
#define GET_RESERVOIR_TEXT "Enter the reservoir code to evaluate its impact: "
#define GET_STATION_TEXT "Enter the pumping station code to evaluate its impact: "

#define RESET   "\033[0m"
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define RED     "\033[31m"


void Menu::clearTerminal(){
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

Menu::Menu(NetworkController* control) {
    this->controller = control;
    this->running = true;
    this->run_menu();
}

void Menu::waitForContinue() {
    std::cout << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
    clearTerminal();
}


void Menu::showMainMenu() {
    // ANSI escape codes for color

    std::cout << "\n=== " << BOLDBLUE << "Water Supply Management Analysis System Menu" << RESET << " ===\n";
    std::cout << BOLDYELLOW << "1. Calculate Maximum Flow of the network\n";
    std::cout << "2. Calculate Maximum Flow to a City\n";
    std::cout << "3. List Cities with Water Deficits\n";
    std::cout << "4. Analyze Impact of Reservoir Removal\n";
    std::cout << "5. Analyze Impact of Pumping Station Removal\n";
    std::cout << "6. Exit\n" << RESET;
    std::cout << "Select an option: ";
}


void Menu::run_menu() {
    while(running){
        this->showMainMenu();
        char choice;
        std::cin >> choice;
        switch (choice - '0') {
            case 1:
                this->showMaxFlowResult();
                break;
            case 2:
                this->showMaxFlowToCity();
                break;
            case 3:
                this->showCitiesWithDeficit();
                break;
            case 4:
                this->showReservoirRemoval();
                break;
            case 5:
                this->showStationRemoval();
                break;
            case 6:
                this->running = false;
                break;
            default:
                std::cout << "Invalid option!\n";
                break;
        }

        this->waitForContinue();
    }
}

void Menu::showMaxFlowResult() {
    auto pairCityFlowVector = controller->getNetworkFlow();
    double totalFlow = 0;

    std::cout <<"Code, Flow"  << std::endl;
    for(const std::pair<std::string, double>& pair: pairCityFlowVector){
        totalFlow += pair.second;
        std::cout << BOLDBLUE << pair.first << RESET <<", " << BOLDGREEN << pair.second << RESET << std::endl;
    }
    std::cout << "Total flow is " << BOLDGREEN << totalFlow << RESET << std::endl;
}

void Menu::showMaxFlowToCity() {
    std::string cityCode = this->getInput(GET_CITY_TEXT);
    City* vertex = dynamic_cast<City*>(this->controller->getVertex(cityCode));
    if(vertex == nullptr){
        std::cout << RED << "City code was not found!" << RESET << std::endl;
        return;
    }

    auto pairCityFlow = controller->getMaxFlowInCity(cityCode);
    std::cout << "City " << vertex->getCode() << " - " << vertex->getName() << std::endl;
    std::cout << "  * Demand: " << vertex->getDemand() << std::endl;
    std::cout << "  * Actual Flow: " << pairCityFlow.second << std::endl;
}


std::string Menu::getInput(const std::string &out) {
    std::string result;
    std::cout << out;
    std::cin >> result;
    return result;
}


void Menu::displayCityInfo(const std::string& code,const std::string& cityName, int demand, int actualFlow, int deficit) {
    std::cout << code << " - "<<   cityName << std::endl;
    std::cout << "  ● Demand: " << demand << std::endl;
    std::cout << "  ● Actual Flow: " << actualFlow << std::endl;
    std::cout << "  ● Deficit: " << RED << deficit << RESET << std::endl;
}

void Menu::showCitiesWithDeficit() {
    double totalDeficit = 0;


    auto pairCityFlowVector = controller->getLowWaterCities();
    if(pairCityFlowVector.empty()) {
        std::cout << "All cities have their water demands fully met.\n";
        return;
    }

    std::cout << "Code, Demand, Actual Flow, Deficit (m3)\n";
    for(const std::pair<std::string, double>& pair: pairCityFlowVector){
        totalDeficit += pair.second;
        City* vertex = dynamic_cast<City*>(this->controller->getVertex(pair.first));
        if(vertex == nullptr) continue;

        this->displayCityInfo(vertex->getCode(), vertex->getName(), vertex->getDemand(), vertex->getDemand() - pair.second, pair.second);
    }
}

void Menu::showReservoirRemoval() {
    std::string res = this->getInput(GET_RESERVOIR_TEXT);
    if(dynamic_cast<WaterReservoir*>(this->controller->getVertex(res)) == nullptr){
        std::cout << "No such station\n";
        return;
    }

    auto pairCityFlowVector = controller->getAffectedByReservoir(res);
    if(!pairCityFlowVector.empty()) {
        std::cout << std::left << std::setw(15) << "City"
                  << std::setw(15) << "Old Flow"
                  << std::setw(15) << "New Flow" << std::endl;
        for (const auto& pair : pairCityFlowVector) {
            std::cout << std::left << std::setw(15) << pair.first
                      << std::setw(15) << pair.second.first
                      << std::setw(15) << pair.second.second << std::endl;
        }
    }
    else
        std::cout << "No city is affected\n";
}

void Menu::showStationRemoval() {
    std::string res = this->getInput(GET_STATION_TEXT);
    if(dynamic_cast<PumpingStation*>(this->controller->getVertex(res)) == nullptr){
        std::cout << "No such station\n";
        return;
    }

    auto pairCityFlowVector = controller->getAffectedByStation(res);

    if(!pairCityFlowVector.empty()) {
        std::cout << std::left << std::setw(15) << "City"
                  << std::setw(15) << "Old Flow"
                  << std::setw(15) << "New Flow" << std::endl;
        for (const auto& pair : pairCityFlowVector) {
            std::cout << std::left << std::setw(15) << pair.first
                      << std::setw(15) << pair.second.first
                      << std::setw(15) << pair.second.second << std::endl;
        }
    }
    else
        std::cout << "No city is affected\n";
}




