/// @file exercises.h
/// @brief Declaration of Exerciser class and its methods.
/// @details This file contains the declaration of the Exerciser class, which provides multiple exercises related to route planning using graph algorithms.

#ifndef DAPROJ2_EXERCISES_H
#define DAPROJ2_EXERCISES_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include "menu.h"
#include "Reader/Reader.h"

/**
 * @class Exerciser
 * @brief A class that contains various exercises related to route calculation.
 */
class Exerciser{
public:


    // TODO add Reader &reader as argument for all the exerciser functions
    void ex_2_1(Reader &reader);

    void ex_2_2(Reader &reader);

    void ex_2_3(Reader &reader);

    void ex_2_4(Reader &reader);

    void ex_3_1(Reader &reader);
};

#endif //DAPROJ2_EXERCISES_H
