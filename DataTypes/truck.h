#ifndef DA_PROJECT_2_TRUCK_H
#define DA_PROJECT_2_TRUCK_H

#include <string>

using namespace std;

class Truck {

public:
    void readTrucks(string filename);
    unsigned int capacity;
    unsigned int  pallets;
};


#endif //DA_PROJECT_2_TRUCK_H
