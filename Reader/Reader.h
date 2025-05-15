#ifndef DA_PROJECT_2_READER_H
#define DA_PROJECT_2_READER_H

#include "../DataTypes/pallet.h"
#include "../DataTypes/truck.h"
#include <vector>
#include <string>

using namespace std;

class Reader {

public:
    void readData(std::string filesNumber);

    std::vector<Pallet> pallets;
    Truck truck;
};


#endif //DA_PROJECT_2_READER_H
