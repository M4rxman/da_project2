/**
 * @file Reader.cpp
 * @brief Implements the Reader class for loading truck and pallet data from CSV files.
 *
 * This file defines the Reader::readData method, which opens two CSV files:
 *  - "../datasets/TruckAndPallets_0<filesNumber>.csv" to read truck capacity and number of pallets
 *  - "../datasets/Pallets_0<filesNumber>.csv" to read individual pallet entries
 * The method populates the Reader::truck member and the Reader::pallets vector.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "Reader.h"

/**
 * @brief Reads truck and pallet information from two CSV files.
 *
 * Given a string suffix `filesNumber`, this function constructs the paths:
 *   "../datasets/TruckAndPallets_0<filesNumber>.csv"
 *   "../datasets/Pallets_0<filesNumber>.csv"
 * It first opens the truck file and reads the header plus one data row
 * to set `truck.capacity` and `truck.pallets`. Then it opens the pallets
 * file, skips its header, and reads up to `truck.pallets` entries,
 * converting each line into a Pallet object and appending it to `pallets`.
 *
 * If either file fails to open, an error message is written to std::cerr
 * and the function returns early without throwing exceptions.
 *
 * @param filesNumber  Numeric suffix (e.g. "1", "2") used to build
 *                     the dataset filenames.
 */
void Reader::readData(const std::string &filesNumber) {
    std::string line;

    // Open truck data file
    std::ifstream file("../datasets/TruckAndPallets_0" + filesNumber + ".csv");
    if (!file.is_open()) {
        std::cerr << "Error: Failed to open truck file " << filesNumber << std::endl;
        return;
    }

    // Skip header line
    std::getline(file, line);
    std::string tmp_capacity, tmp_pallets;
    // Read capacity and pallet count
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::getline(ss, tmp_capacity, ',');
        std::getline(ss, tmp_pallets, ',');
        truck.capacity = std::strtoul(tmp_capacity.c_str(), nullptr, 0);
        truck.pallets  = std::strtoul(tmp_pallets.c_str(), nullptr, 0);
    }
    file.close();

    // Open pallets data file
    std::ifstream Pfile("../datasets/Pallets_0" + filesNumber + ".csv");
    if (!Pfile.is_open()) {
        std::cerr << "Error: Failed to open pallets file " << filesNumber << std::endl;
        return;
    }

    // Skip header line
    std::getline(Pfile, line);

    unsigned int i = 0;
    std::string tmp_pallet_num, tmp_pallet_weight, tmp_pallet_profit;

    // Read each pallet record up to the declared count
    while ((std::getline(Pfile, line)) && i < truck.pallets) {
        std::stringstream ss(line);
        std::getline(ss, tmp_pallet_num, ',');
        std::getline(ss, tmp_pallet_weight, ',');
        std::getline(ss, tmp_pallet_profit, ',');

        Pallet pal(
            std::stoi(tmp_pallet_num),
            std::stoi(tmp_pallet_weight),
            std::stoi(tmp_pallet_profit)
        );
        this->pallets.push_back(pal);
        ++i;
    }
    Pfile.close();
}
