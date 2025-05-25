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
 * @brief Hosts implementations of several optimization exercises.
 *
 * Provides methods:
 *  - ex_2_1: brute-force knapsack
 *  - ex_2_2: dynamic-programming knapsack
 *  - ex_2_3: greedy knapsack
 *  - ex_2_4: genetic algorithm knapsack
 */
class Exerciser{
public:
    /**
     * @brief Brute-force enumeration for 0/1 Knapsack.
     * @param reader  Supplies pallets and truck capacity.
     */
    void ex_2_1(Reader &reader);

    /**
         * @brief Dynamic-programming solution for 0/1 Knapsack.
         * @param reader  Supplies pallets and truck capacity.
         */
    void ex_2_2(Reader &reader);

    /**
     * @brief Greedy ratio-based heuristic for knapsack.
     * @param reader  Supplies pallets and truck capacity.
     */
    void ex_2_3(Reader &reader);

    /**
     * @brief Genetic-algorithm approach for knapsack.
     * @param reader  Supplies pallets and truck capacity.
     */
    void ex_2_4(Reader &reader);

};

#endif //DAPROJ2_EXERCISES_H
