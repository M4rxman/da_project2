/**
* @file exercises.cpp
 * @brief Implements the main knapsack and routing exercises in Exerciser.
 *
 * Contains four algorithms for the 0/1 Knapsack problem and one placeholder:
 *  - ex_2_1: brute-force enumeration
 *  - ex_2_2: dynamic programming
 *  - ex_2_3: greedy ratio heuristic
 *  - ex_2_4: genetic algorithm
 *  - ex_3_1: (TODO, not documented)
 */
#include "exercises.h"
#include <algorithm>
#include <iomanip>
#include <random>
#include <chrono>

const int GA_POP_SIZE = 100;
const double GA_MUTATION_RATE = 0.01;
const int GA_MAX_GENERATIONS = 100;


/**
 * @brief Brute-force solution to the 0/1 Knapsack problem.
 *
 * Tries every subset of pallets by bitmask enumeration, tracking
 * the best(>profit) subset that fits within truck.capacity.
 *
 * @complexity
 * - Time:    O(2^n * n), where n = number of pallets
 * - Space:   O(1) extra (aside from input storage)
 *
 * @param reader  Provides reader.pallets and reader.truck.capacity.
 */

void Exerciser::ex_2_1(Reader &reader) {
    const vector<Pallet> &palletList = reader.pallets;
    const size_t   palletCount = palletList.size();
    const int capacity    = reader.truck.capacity;

    int bestTotalProfit = 0;
    int bestSubsetMask  = 0;
    int finalWeight = 0;

    auto start = std::chrono::high_resolution_clock::now();

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

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(end - start);

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
    std::cout << "Execution time: " << std::fixed << std::setprecision(3)
                  << duration.count() << " ms\n";
    std::cout << "===========================================\n";
};


/**
 * @brief Dynamic-programming solution to the 0/1 Knapsack problem.
 *
 * Builds a 2D table dp[i][w] = max profit using first i items and capacity w,
 * then backtracks to retrieve the chosen set.
 *
 * @complexity
 * - Time:    O(n * W), where W = truck.capacity
 * - Space:   O(n * W) for the DP table
 *
 * @param reader  Provides reader.pallets and reader.truck.capacity.
 */
void Exerciser::ex_2_2(Reader &reader) {
    const auto &palletList = reader.pallets;
    const size_t n = palletList.size();
    const int capacity = reader.truck.capacity;

    // dp[i][w] = max profit using the first i pallets with capacity limit w
    std::vector<std::vector<int>> dp(n+1, std::vector<int>(capacity+1, 0));

    auto start = std::chrono::high_resolution_clock::now();

    for (size_t i = 1; i <= n; ++i) {
        int wt = palletList[i-1].weight;
        int pf = palletList[i-1].profit;
        for (int w = 0; w <= capacity; ++w) {
            // either skip pallet i, or take it (if it fits)
            dp[i][w] = dp[i-1][w];
            if (wt <= w) {
                dp[i][w] = std::max(dp[i][w], dp[i-1][w - wt] + pf);
            }
        }
    }

    // The best total profit is at dp[n][capacity]
    int bestTotalProfit = dp[n][capacity];

    // Find the actual weight used: the smallest w such that dp[n][w] == bestTotalProfit
    int finalWeight = 0;
    for (int w = 0; w <= capacity; ++w) {
        if (dp[n][w] == bestTotalProfit) {
            finalWeight = w;
            break;
        }
    }

    // Backtrack to find which pallets were taken
    std::vector<bool> taken(n, false);
    int w = finalWeight;
    for (int i = n; i >= 1; --i) {
        if (dp[i][w] != dp[i-1][w]) {
            // pallet (i-1) was taken
            taken[i-1] = true;
            w -= palletList[i-1].weight;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(end - start);

    // Output results
    std::cout << "=== Ex. 2.2: Dynamic Programming Knapsack ===\n";
    std::cout << "Truck Capacity: "    << capacity  << "\n";
    std::cout << "Available pallets: " << n         << "\n\n";
    std::cout << "Final weight: "      << finalWeight    << "\n";
    std::cout << "Best overall profit: "<< bestTotalProfit << "\n";
    std::cout << "Selected pallets:\n";
    for (size_t i = 0; i < n; ++i) {
        if (taken[i]) {
            const auto &p = palletList[i];
            std::cout << "  - Pallet #" << p.number
                      << " | Weight: "  << p.weight
                      << " | Profit: "  << p.profit
                      << "\n";
        }
    }
    std::cout << "Execution time: " << std::fixed << std::setprecision(3)
                  << duration.count() << " ms\n";
    std::cout << "===========================================\n";
};


/**
 * @brief Greedy heuristic: sort by weight/profit ratio and take in order.
 *
 * @complexity
 * - Time:    O(n log n) for the sort
 * - Space:   O(n) auxiliary for ratio–index pairs
 *
 * @param reader  Provides reader.pallets and reader.truck.capacity.
 */
void Exerciser::ex_2_3(Reader &reader) {
    Truck& truck = reader.truck;
    std::vector<Pallet>& pallets = reader.pallets;

    auto start = std::chrono::high_resolution_clock::now();

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

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(end - start);

    std::cout << "=== Ex. 2.3: Greedy Algorithm ===\n";
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
    std::cout << "Execution time: " << std::fixed << std::setprecision(3)
                  << duration.count() << " ms\n";
    std::cout << "===========================================\n";
};



int calculate_fitness(const vector<bool>& chromosome, const vector<Pallet>& pallets, int truck_capacity) {
    int total_value = 0;
    int total_weight = 0;

    for(int i = 0; i < chromosome.size(); i++) {
        if(chromosome[i]) {
            total_value += pallets[i].profit;
            total_weight += pallets[i].weight;
        }
    }
    return (total_weight > truck_capacity) ? -1 : total_value;
}

void repair_solution(vector<bool>& chromosome, const vector<Pallet>& pallets, int truck_capacity) {
    int total_weight = 0;
    vector<pair<double, int>> items;

    for(int i = 0; i < chromosome.size(); i++) {
        if(chromosome[i]) {
            total_weight += pallets[i].weight;
            items.emplace_back(
                    static_cast<double>(pallets[i].profit)/pallets[i].weight,
                    i
            );
        }
    }

    sort(items.begin(), items.end());

    int idx = 0;
    while(total_weight > truck_capacity && idx < items.size()) {
        int item_idx = items[idx].second;
        chromosome[item_idx] = false;
        total_weight -= pallets[item_idx].weight;
        idx++;
    }
}

/**
 * @struct Individual
 * @brief Represents one candidate solution in the genetic algorithm.
 *
 * Each Individual contains:
 *   - chromosome: a bit-vector where each bit indicates whether the
 *     corresponding pallet is included in this solution.
 *   - fitness: the computed profit for this chromosome (or –1 if it
 *     exceeds the truck’s capacity).
 */
struct Individual {
    vector<bool> chromosome;
    int fitness;
};


/**
 * @brief Genetic-algorithm approach to Knapsack.
 *
 * Initializes a population of random bitstrings, repairs overweight
 * individuals, then evolves via tournament selection, single-point
 * crossover, and bit-flip mutation.
 *
 * @complexity
 * - Time:    O(G * P * n), where
 *            G = GA_MAX_GENERATIONS,
 *            P = GA_POP_SIZE,
 *            n = number of pallets
 * - Space:   O(P * n) for the population
 *
 * @param reader  Provides reader.pallets and reader.truck.capacity.
 */
void Exerciser::ex_2_4(Reader &reader) {

    Truck& truck = reader.truck;
    std::vector<Pallet>& pallets = reader.pallets;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> bin_dist(0, 1);

    auto start = std::chrono::high_resolution_clock::now();

    // Initialize population
    vector<Individual> population(GA_POP_SIZE);

    for(Individual& ind : population) {
        ind.chromosome.resize(pallets.size());
        for(int i = 0; i < pallets.size(); i++) {
            ind.chromosome[i] = bin_dist(gen);
        }
        repair_solution(ind.chromosome, pallets, truck.capacity);
        ind.fitness = calculate_fitness(ind.chromosome, pallets, truck.capacity);
    }

    for(int generation = 0; generation < GA_MAX_GENERATIONS; generation++) {
        vector<Individual> new_population;

        // Elitism: Keep top 10%
        sort(population.begin(), population.end(),
             [](const Individual& a, const Individual& b) {
                 return a.fitness > b.fitness;
             });
        for(int i = 0; i < GA_POP_SIZE/10; i++) {
            new_population.push_back(population[i]);
        }


        while(new_population.size() < GA_POP_SIZE) {

            // Tournament
            uniform_int_distribution<> tourn_dist(0, population.size()-1);
            Individual parent1 = population[tourn_dist(gen)];
            Individual parent2 = population[tourn_dist(gen)];
            if(parent2.fitness > parent1.fitness) swap(parent1, parent2);

            // Crossover
            uniform_int_distribution<> cross_dist(0, pallets.size()-1);
            int crossover_point = cross_dist(gen);
            Individual child;

            child.chromosome.insert(child.chromosome.end(),
                                    parent1.chromosome.begin(),
                                    parent1.chromosome.begin() + crossover_point);
            child.chromosome.insert(child.chromosome.end(),
                                    parent2.chromosome.begin() + crossover_point,
                                    parent2.chromosome.end());

            // Mutation
            uniform_real_distribution<> mut_dist(0.0, 1.0);

            for (int i = 0; i < child.chromosome.size(); i++) {
                if (mut_dist(gen) < GA_MUTATION_RATE) {
                    child.chromosome[i] = !child.chromosome[i];
                }
            }

            repair_solution(child.chromosome, pallets, truck.capacity);
            child.fitness = calculate_fitness(child.chromosome, pallets, truck.capacity);
            new_population.push_back(child);
        }

        population = new_population;
    }

    sort(population.begin(), population.end(),
         [](const Individual& a, const Individual& b) {
             return a.fitness > b.fitness;
         });
    Individual& best = population[0];

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(end - start);

    std::cout << "=== Ex. 2.4: Genetic Algorithm ===\n";
    std::cout << "Truck Capacity: " << truck.capacity << "\n";
    std::cout << "Available pallets: " << truck.pallets << "\n\n";
    int total_weight = 0;
    vector<const Pallet*> selected_pallets;

    for(int idx = 0; idx < best.chromosome.size(); idx++) {
        if(best.chromosome[idx]) {
            selected_pallets.push_back(&pallets[idx]);
            total_weight += pallets[idx].weight;
        }
    }

    std::cout << "Best overall profit: " << best.fitness << "\n";
    std::cout << "Final weight: " << total_weight << "\n";
    std::cout << "Selected pallets: " << selected_pallets.size() << "\n";

    for(const Pallet* p : selected_pallets) {
        std::cout << "  - Pallet #" << p->number
                  << " | Weight: " << p->weight
                  << " | Profit: " << p->profit
                  << " | Profit/Weight: " << std::fixed << std::setprecision(2)
                  << static_cast<double>(p->profit)/p->weight
                  << "\n";
    }
    std::cout << "Execution time: " << std::fixed << std::setprecision(3)
                  << duration.count() << " ms\n";
    std::cout << "===========================================\n";
}




void Exerciser::ex_3_1(Reader &reader) {
    // TODO
};

