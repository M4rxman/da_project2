#ifndef DA_PROJECT_2_READER_H
#define DA_PROJECT_2_READER_H

#include "../DataTypes/pallet.h"
#include "../DataTypes/truck.h"
#include "list"
#include <string>

using namespace std;

class Reader {

public:
    void readData(string filename,  Pallet* pallets[], Truck truck);

    Pallet* pallets[];
    Truck truck;
};


#endif //DA_PROJECT_2_READER_H
