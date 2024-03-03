#include <iostream>
#include "../ReadData/readData.h"
#include "../Code/Menu.h"

int main() {
    cout << "\n" << "Getting information...." << "\n";

    readData data;
    data.readReservoirs();
    data.readStations();
    data.readCities();
    data.readPipes();
    cout << "Information acquired!" << "\n" << "\n";

    //Menu menu;
    //menu.menu();

    return 0 ;
}