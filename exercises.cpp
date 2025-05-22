
#include "exercises.h"
#include <algorithm>
#include <iomanip>


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
    int finalWeight = 0;

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
            finalWeight = currentWeight;
        }
    }

    cout << "=== Ex. 2.1: Brute-Force Knapsack ===\n";
    cout << "Truck Capacity: " << capacity << "\n";
    cout << "Available pallets: " << palletCount << "\n\n";
    std::cout << "Final weight: " << finalWeight << "\n";

    cout << "Best overall profit: " << bestTotalProfit << "\n";
    cout << "Selected pallets:\n";
    for (size_t i = 0; i < palletCount; ++i) {
        if (bestSubsetMask & (1ULL << i)) {
            const auto &p = palletList[i];
            cout << "  - Pallet #" << p.number
                 << " | Weight: "  << p.weight
                 << " | Profit: "<< p.profit
                 << "\n";
        }
    }

};


void Exerciser::ex_2_2(Reader &reader) {
    // TODO
};


void Exerciser::ex_2_3(Reader &reader) {
    Truck& truck = reader.truck;
    std::vector<Pallet>& pallets = reader.pallets;

    std::vector<std::pair<double, int>> ratioIndexPairs;
    for (int i = 0; i < pallets.size(); ++i) {
        double ratio = static_cast<double>(pallets[i].weight) / pallets[i].profit;
        ratioIndexPairs.emplace_back(ratio, i);
    }

    std::sort(ratioIndexPairs.begin(), ratioIndexPairs.end(),
              [](const auto& a, const auto& b) { return a.first < b.first; });

    unsigned currentWeight = 0;
    unsigned totalProfit = 0;
    std::vector<int> selectedIndices;

    for (const auto& [ratio, idx] : ratioIndexPairs) {
        const Pallet& p = pallets[idx];
        if (currentWeight + p.weight <= truck.capacity) {
            selectedIndices.push_back(idx);
            currentWeight += p.weight;
            totalProfit += p.profit;
        }
    }

    std::cout << "=== Ex. 2.4: Greedy Algorithm ===\n";
    std::cout << "Truck Capacity: " << truck.capacity << "\n";
    std::cout << "Available pallets: " << truck.pallets << "\n\n";

    std::cout << "Best overall profit: " << totalProfit << "\n";
    std::cout << "Final weight: " << currentWeight << "\n";
    std::cout << "Selected pallets:\n";

    for (int idx : selectedIndices) {
        const Pallet& p = pallets[idx];
        std::cout << "  - Pallet #" << p.number
                  << " | Weight: " << p.weight
                  << " | Profit: " << p.profit
                  << " | Profit/Weight: " << std::fixed << std::setprecision(2)
                  << static_cast<double>(p.profit)/p.weight
                  << "\n";
    }

};


void Exerciser::ex_2_4(Reader &reader) {

}




void Exerciser::ex_2_5(Reader &reader) {
    // TODO
};