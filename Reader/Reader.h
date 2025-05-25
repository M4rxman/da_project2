/**
* @file Reader.h
 * @brief Declares the Reader class for loading truck and pallet data from CSV files.
 *
 * The Reader class provides a single public method, readData(),
 * which reads two CSV files:
 *   - TruckAndPallets_0<filesNumber>.csv
 *   - Pallets_0<filesNumber>.csv
 * and populates its `truck` member (capacity and pallet count)
 * and its `pallets` vector (individual Pallet objects).
 */

#ifndef DA_PROJECT_2_READER_H
#define DA_PROJECT_2_READER_H

#include "../DataTypes/pallet.h"
#include "../DataTypes/truck.h"
#include <vector>
#include <string>

/**
 * @class Reader
 * @brief Loads and stores truck parameters and pallet listings from CSV datasets.
 */
class Reader {
public:
    /**
     * @brief Reads the truck and pallet files corresponding to a dataset index.
     *
     * Constructs file paths:
     *   "../datasets/TruckAndPallets_0<filesNumber>.csv"
     *   "../datasets/Pallets_0<filesNumber>.csv"
     * Opens each file in turn, parses the header and data lines,
     * and fills:
     *   - truck.capacity
     *   - truck.pallets  (number of pallets expected)
     *   - pallets        (vector of Pallet objects)
     *
     * If a file fails to open, an error is printed and the function returns early.
     *
     * @param filesNumber
     *   Two-digit suffix (e.g. "1", "2", "03") used to build the filenames.
     */
    void readData(const std::string &filesNumber);

    std::vector<Pallet> pallets;  /**< List of loaded Pallet objects */
    Truck              truck;    /**< Loaded Truck object (capacity and pallet count) */
};

#endif // DA_PROJECT_2_READER_H
