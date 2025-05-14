#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>


/**
 * @brief The menu class provides a user interface for interacting with the route planning system.
 */
class menu {

private:

    std::string filesNumber;

public:
    /**
     * @brief Constructs the menu and displays a welcome message.
     */
    menu();

    /**
     * @brief Displays the main menu and handles user input for different modes.
     *
     */
    void mainMenu();

    void dataMenu();

    /**
     * @brief Returns to the previous menu or repeats commands.
     */
    void backToMenu(menu& m);
};

#endif // MENU_H
