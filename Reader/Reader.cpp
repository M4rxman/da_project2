//
// Created by alex2 on 5/14/2025.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <vector>


#include "Reader.h"

void Reader::readData(std::string filesNumber) {

    std::string line;

    std::ifstream file("../datasets/TruckAndPallets_0" + filesNumber + ".csv");
    if (!file.is_open()) {
        std::cerr << "Error: Failed to open truck file " << filesNumber << std::endl;
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
    file.close();

    std::ifstream Pfile("../datasets/Pallets_0" + filesNumber + ".csv");
    if (!Pfile.is_open()) {
        std::cerr << "Error: Failed to open pallets file " << filesNumber << std::endl;
        return;
    }

    //reading pallets
    std::getline(Pfile, line, '\n');

    unsigned int  i = 0;
    std::string tmp_pallet_num, tmp_pallet_weight, tmp_pallet_profit;

    while ((std::getline(Pfile, line, '\n')) && i <= truck.pallets) {
        std::stringstream ss(line);

        std::getline(ss, tmp_pallet_num, ',');
        std::getline(ss, tmp_pallet_weight, ',');
        std::getline(ss, tmp_pallet_profit, ',');

        Pallet pal(std::stoi(tmp_pallet_num),std::stoi(tmp_pallet_weight),std::stoi(tmp_pallet_profit));
        this->pallets.push_back(pal);
    }
    Pfile.close();
}