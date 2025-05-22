#include "menu.h"
#include "exercises.h"
#include <chrono>
#include <iomanip>
#include "Reader/Reader.h"

#define BRUTE_FORCE 1
#define DYNAMIC 2
#define GREEDY 3
#define ILP 4
#define PERFORMANCE 5
#define QUIT 0
#define DATASET_MENU 9


/**
 * @brief Constructs the menu and displays a welcome message.
 */
menu::menu() {
    std::cout << "Welcome to the menu\n";
}

/**
 * @brief Displays the main menu and handles user input for different modes.
 *
 */

void menu::mainMenu() {
    std::cout << "============================================================\n";
    std::cout << "          Delivery Truck Pallet Packing - Main Menu         \n";
    std::cout << "============================================================\n";
    std::cout << " 1. Exhaustive/Brute-Force Approach ( 2.1 )\n";
    std::cout << " 2. Dynamic Programming Approach ( 2.2 )\n";
    std::cout << " 3. Approximation Algorithms/Greedy Approach ( 2.3 )\n";
    std::cout << " 4. Integer Linear Programming Algorithm ( 2.4 )\n";
    std::cout << " 5. Performance Evaluation\n\n";

    std::cout << " 9. Go Back to Dataset Menu\n";
    std::cout << " 0. Quit\n";
    std::cout << "-------------------------------------\n";
    std::cout << " Choose an option:\n";

    int mode;
    std::cin >> mode;

    Reader reader;

    // TODO fix this according to the new reading functions
    reader.readData(this->filesNumber);

    Exerciser exerciser;

    if (mode == BRUTE_FORCE) {
        std::cout << "=== Exhaustive/Brute Force Approach ===\n";
        auto start = std::chrono::high_resolution_clock::now();
        exerciser.ex_2_1(reader);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration<double, std::milli>(end - start);
        std::cout << "Execution time: " << std::fixed << std::setprecision(3)
                  << duration.count() << " ms\n";
        std::cout << "===========================================\n";
        backToMenu(*this);
    }
    else if (mode == DYNAMIC) {
        std::cout << "=== Dynamic Programming Approach ===\n";
        auto start = std::chrono::high_resolution_clock::now();
        exerciser.ex_2_2(reader);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration<double, std::milli>(end - start);
        std::cout << "Execution time: " << std::fixed << std::setprecision(3)
                  << duration.count() << " ms\n";
        std::cout << "===========================================\n";
        backToMenu(*this);
    }
    else if (mode == GREEDY) {
        std::cout << "=== Approximation Algorithms/Greedy Approach ===\n";
        auto start = std::chrono::high_resolution_clock::now();
        exerciser.ex_2_3(reader);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration<double, std::milli>(end - start);
        std::cout << "Execution time: " << std::fixed << std::setprecision(3)
                  << duration.count() << " ms\n";
        std::cout << "===========================================\n";
        backToMenu(*this);
    }
    else if (mode == ILP) {
        std::cout << "=== Integer Linear Programming Algorithm ===\n";
        auto start = std::chrono::high_resolution_clock::now();
        exerciser.ex_2_4(reader);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration<double, std::milli>(end - start);
        std::cout << "Execution time: " << std::fixed << std::setprecision(3)
                  << duration.count() << " ms\n";
        std::cout << "===========================================\n";
        backToMenu(*this);
    }
    else if (mode == PERFORMANCE) {
        std::cout << "Performance Evaluation \n ";

        exerciser.ex_3_1(reader);

        backToMenu(*this);
    }
    else if (mode == QUIT) {
        std::cout << "Exiting program...\n";
        exit(0);
    }
    else if (mode == DATASET_MENU) {
        std::cout << "Going back to the Dataset Menu...\n";
        this->dataMenu();
        this->mainMenu();
        exit(0);
    }
    else {
        std::cout << "Invalid option. Please try again.\n";

        mainMenu();
    }
}

void menu::dataMenu() {
    std::cout << "============================================================\n";
    std::cout << "          Delivery Truck Pallet Packing - Data Menu         \n";
    std::cout << "============================================================\n";
    std::cout << "Select a number between 1 and 4 to choose a dataset:\n";

    int dataset;
    std::cin >> dataset;

    this->filesNumber = std::to_string(dataset);

}


void menu::backToMenu(menu& m) {
    std::cout << "\n-------------------------------------\n";
    std::cout << "Choose 9 to return to the menu or press any other key to exit\n";

    char choice;
    std::cin >> choice;

    if (choice == '9') {
        m.mainMenu();
    } else {
        std::cout << "Exiting program...\n";
        exit(0);
    }
}