#ifndef DA_PROJECT_2_PALLETS_H
#define DA_PROJECT_2_PALLETS_H

#include <string>

using namespace std;

class Pallet {

public:
    unsigned int  number;
    unsigned int  weight;
    unsigned int  profit;
    void readPallets(string filename);

};


#endif //DA_PROJECT_2_PALLETS_H
