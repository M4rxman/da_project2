//
// Created by alex2 on 5/14/2025.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string>

#include "Reader.h"

void Reader::readData(std::string filename, Pallet* pallets[], Truck truck) {

    std::string line;

    std::ifstream file("../datasets/TruckAndPallets_" + filename);
    if (!file.is_open()) {
        std::cerr << "Error: Failed to open file " << filename << std::endl;
        return;
    }

    //reading trucks
    // Skip header line
    std::getline(file, line, '\n');
    std::string tmp_capacity, tmp_pallets;
    while (std::getline(file, line, '\n')) {
        std::stringstream ss(line);



        std::getline(ss, tmp_capacity, ',');
        std::getline(ss, tmp_pallets, ',');

        truck.capacity = std::strtoul(tmp_capacity.c_str(), nullptr, 0);
        truck.pallets = std::strtoul(tmp_pallets.c_str(), nullptr, 0);
    }

    //TODO: close stream, open one for pallets;

    //reading pallets
    std::getline(file, line, '\n');

    unsigned int  i = 0;
    std::string tmp_pallet_num, tmp_pallet_weight, tmp_pallet_profit;

    while ((std::getline(file, line, '\n')) && i <= truck.pallets) {
        std::stringstream ss(line);



        std::getline(ss, tmp_pallet_num, ',');
        std::getline(ss, tmp_pallet_weight, ',');
        std::getline(ss, tmp_pallet_profit, ',');

        pallets[i]->number = std::strtoul(tmp_pallet_num.c_str(), nullptr, 0);
        pallets[i]->weight = std::strtoul(tmp_pallet_weight.c_str(), nullptr, 0);
        pallets[i]->profit = std::strtoul(tmp_pallet_profit.c_str(), nullptr, 0);
        i++;
    }
}