/**
* @file truck.h
 * @brief Declares the Truck class, which holds capacity and pallet count.
 *
 * The Truck class represents a delivery truck’s load limits:
 *  - capacity: maximum total weight the truck can carry
 *  - pallets:  expected number of pallets to load
 * It also provides a method to read these values from a CSV file.
 */

#ifndef DA_PROJECT_2_TRUCK_H
#define DA_PROJECT_2_TRUCK_H

#include <string>

/**
 * @class Truck
 * @brief Stores the capacity and pallet count of a delivery truck.
 */
class Truck {
public:
    /**
     * @brief Loads the truck’s capacity and pallet count from a CSV file.
     *
     * Expects the file to contain two comma-separated values:
     *   capacity,pallets
     * on a single line (after an optional header). On failure to open
     * the file, writes an error to std::cerr.
     *
     * @param filename  Path to the CSV file to read.
     */
    void readTrucks(const std::string &filename);

    unsigned int capacity; /**< Maximum weight capacity of the truck. */
    unsigned int pallets;  /**< Number of pallets expected for loading. */
};

#endif // DA_PROJECT_2_TRUCK_H
