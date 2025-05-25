/**
* @file pallet.h
 * @brief Declaration of pallet class, which represents a weight and profit.
 */
#ifndef DA_PROJECT_2_PALLETS_H
#define DA_PROJECT_2_PALLETS_H

#include <string>

using namespace std;

/**
 * @class Pallet
 * @brief Stores pallet information (id, weight and profit).
 */
class Pallet {

public:
    /**
     * @brief Constructor.
     * @param number Identifier.
     * @param weight Pallet's weight (load unit).
     * @param profit Profit uppon delivery of the pallet.
     */
    Pallet(unsigned int  number,unsigned int  weight,unsigned int  profit);
    Pallet();

    unsigned int  number;
    unsigned int  weight;
    unsigned int  profit;
    void readPallets(string filename);

};


#endif //DA_PROJECT_2_PALLETS_H
