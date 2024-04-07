#ifndef DA_PROJECT_23_24_MENU_H
#define DA_PROJECT_23_24_MENU_H

#include "NetworkController.h"
#include <cstdlib>

/**
 * @class Menu
 * @brief Represents a text-based menu interface for interacting with the network controller.
 */

class Menu{
private:
    NetworkController* controller; /**< Pointer to the NetworkController object */
    bool running = true; /**< Flag indicating whether the menu is running */
public:
    /**
     * @brief Constructs a Menu object with a given NetworkController.
     * Initializes the menu object with a pointer to a NetworkController object, sets the running
     * flag to true, and then calls the run_menu() function to start the menu loop.
     * @param control Pointer to a NetworkController object
     * @complexity O(1)
     */
    Menu(NetworkController* control);

    /**
     * @brief Retrieves user input from the console.
     * Prompts the user with a message provided as a parameter and reads input from the console.
     * @param out Message displayed before input prompt
     * @return String containing user input
     * @complexity O(1)
     */
    static std::string getInput(const std::string& out);

    /**
     * @brief Waits for the user to press a key to continue.
     * Prompts the user to press the Enter key to continue the program execution.
     * It waits for the user input and clears the terminal afterward.
     * @complexity O(1)
     */
    void waitForContinue();

    /**
     * @brief Clears the terminal screen.
     * Clears the terminal screen to provide a clean interface for displaying new content or messages.
     * @complexity O(1)
     */
    void clearTerminal();

    /**
     * @brief Displays the main menu.
     * Displays the main menu of the Water Supply Management Analysis System.
     * @complexity O(1)
     */
    void showMainMenu();

    /**
     * @brief Runs the menu loop.
     * Runs the main menu loop of the Water Supply Management Analysis System. It continuously displays
     * the main menu, prompts the user for input, and executes the corresponding functionality based on the selected option.
     * @complexity O(n), where n is the number of iterations depending on user input.
     */
    void run_menu();

    /**
     * @brief Displays the maximum flow result menu.
     * Shows the maximum flow result of the network by retrieving flow information for each city from the controller object.
     * It then prints the city code and its flow value, along with the total flow for all cities.
     * @complexity O(C), where C is the number of cities.
     */
    void showMaxFlowResult();

    /**
     * @brief Displays the menu for finding maximum flow to a city.
     * Prompts the user to input a city code. It then retrieves information about the maximum flow to the specified city from the controller object.
     * If the city is found, it prints details such as the city code, name, demand, and actual flow.
     * If the city is not found, it displays a message indicating that the city code was not found.
     * @complexity O(1)
     */
    void showMaxFlowToCity();

    /**
     * @brief Displays cities with deficit menu.
     * Retrieves information about cities with water deficits from the controller object. It calculates the total deficit across
     * all cities and displays details such as the city code, demand, actual flow, and deficit for each affected city.
     * If no cities have deficits, it prints a message indicating that all cities have their water demands fully met.
     * @complexity O(C), where C is the number of cities.
     */
    void showCitiesWithDeficit();

    /**
     * @brief Displays information about a city including its deficit.
     * Responsible for displaying information about a city, including its code, name, demand, actual flow, and deficit.
     * @param code City code
     * @param cityName Name of the city
     * @param demand City's demand
     * @param actualFlow Actual flow to the city
     * @param deficit Deficit of the city
     * @complexity O(1)
     */
    void displayCityInfo(const std::string& code,const std::string& cityName, int demand, int actualFlow, int deficit);

    /**
     * @brief Displays the reservoir removal menu.
     * Displays the impact of removing a water reservoir on the flow of water to various cities.
     * It prompts the user to input the reservoir ID, retrieves the affected cities and their flow changes from the controller.
     * If no cities are affected, it informs the user accordingly.
     * @complexity O(C + R), where C is the number of cities and R is the recalculating process complexity.
     */
    void showReservoirRemoval();

    /**
     * @brief Displays the station removal menu.
     * Shows the impact of removing a pumping station on the flow of water to various cities.
     * It prompts the user to input the station ID, retrieves the affected cities and their flow changes from the controller.
     * If no cities are affected, it informs the user accordingly.
     * @complexity O(C + S), where C is the number of cities and S is the recalculating process complexity.
     */
    void showStationRemoval();

    /**
     * @brief Displays the pipeline failure simulation menu.
     * Simulates a pipeline failure and displays the impact on water flow to various cities.
     * It prompts the user to input the origin and destination IDs of the pipeline to simulate failure.
     * Then, it calls the controller's method to obtain the affected cities and their flow changes.
     * If no cities are affected, it informs the user accordingly. If an error occurs, it displays the error message.
     * @complexity O(C + P), where C is the number of cities and P is the complexity of pipeline failure simulation.
     */
    void simulatePipelineFailureHandler();
};

#endif //DA_PROJECT_23_24_MENU_H
