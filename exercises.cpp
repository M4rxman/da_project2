
#include "exercises.h"
/**
 * @file exercises.cpp
 * @brief Implementation of exercise functions for delivery truck optimizations.
 */


void Exerciser::ex_2_1(Reader &reader) {
    const vector<Pallet> &palletList = reader.pallets;
    const size_t   palletCount = palletList.size();
    const int capacity    = reader.truck.capacity;

    int bestTotalProfit = 0;
    int bestSubsetMask  = 0;

    const int totalSubsets = (1ULL << palletCount);
    for (int subsetMask = 0; subsetMask < totalSubsets; ++subsetMask) {
        int currentWeight = 0;
        int currentProfit = 0;

        for (size_t i = 0; i < palletCount; ++i) {
            //If bit i is active, add pallet i
            if (subsetMask & (1ULL << i)) {
                currentWeight += palletList[i].weight;

                if (currentWeight > capacity) {
                    currentProfit = 0;
                    break;
                }
                currentProfit += palletList[i].profit;
            }
        }

        //If it fits and profit >, update bestProfit
        if (currentWeight <= capacity && currentProfit > bestTotalProfit) {
            bestTotalProfit = currentProfit;
            bestSubsetMask  = subsetMask;
        }
    }
    cout << "=== Ex. 2.1: Brute-Force Knapsack ===\n";
    cout << "Truck Capacity: " << capacity << "\n";
    cout << "Número de pallets disponíveis: " << palletCount << "\n\n";

    cout << "Melhor lucro total: " << bestTotalProfit << "\n";
    cout << "Conjunto de pallets selecionados:\n";
    for (size_t i = 0; i < palletCount; ++i) {
        if (bestSubsetMask & (1ULL << i)) {
            const auto &p = palletList[i];
            cout << "  - Pallet #" << p.number
                 << " | Peso: "  << p.weight
                 << " | Profit: "<< p.profit
                 << "\n";
        }
    }
    cout << "====================================\n\n";

};


void Exerciser::ex_2_2(Reader &reader) {
    // TODO
};


void Exerciser::ex_2_3(Reader &reader) {
    // TODO
};


void Exerciser::ex_2_4(Reader &reader) {
    // TODO
};

void Exerciser::ex_2_5(Reader &reader) {
    // TODO
};