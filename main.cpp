#include <iostream>
#include <chrono>
#include <vector>
#include <random>
#include <thread>

#include "Book.h"
#include "Books.h"
#include "ThreadPool.h"

const unsigned int NUMBER_OF_THREADS = std::thread::hardware_concurrency();

// Function to generate random price and quantity updates
std::pair<std::vector<std::pair<double, double>>, std::vector<std::pair<double, double>>> generate_random_updates(int num_updates) {
    std::vector<std::pair<double, double>> bid_updates;
    std::vector<std::pair<double, double>> ask_updates;

    // Random number generator setup
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> price_dist(0.001, 0.01);  // Random prices between 0.001 and 0.01
    std::uniform_real_distribution<> qty_dist(0.0, 100.0);    // Random quantities between 0 and 100

    for (int i = 0; i < num_updates; ++i) {
        // Generate random bid and ask prices and quantities
        double random_bid_price = price_dist(gen);
        double random_bid_qty = qty_dist(gen);

        double random_ask_price = price_dist(gen);
        double random_ask_qty = qty_dist(gen);

        // Append to the bid and ask update lists
        bid_updates.emplace_back(random_bid_price, random_bid_qty);
        ask_updates.emplace_back(random_ask_price, random_ask_qty);
    }

    return { bid_updates, ask_updates };
}

// Benchmark to simulate random updates for 1000-2000 symbols
void benchmarkMultipleSymbols(int numSymbols, int numUpdates) {
    // Create a list of symbols
    std::vector<std::string> symbols;
    for (size_t i = 0; i < numSymbols; ++i) {
        symbols.push_back("Symbol" + std::to_string(i));
    }
        
    books symbolBooks;
    ThreadPool pool(NUMBER_OF_THREADS);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> symbolDist(0, numSymbols - 1);
      

    auto start = std::chrono::high_resolution_clock::now();

    for (size_t i = 0; i < numUpdates; ++i) {
        // Randomly select a symbol and generate random bid/ask updates
        std::string symbol = symbols[symbolDist(gen)];
        // Generate random updates
        auto [bidUpdate, askUpdate] = generate_random_updates(numUpdates);

        // Process the update (in parallel using the thread pool or directly)
        pool.enqueue([symbol, bidUpdate, askUpdate, &symbolBooks]() {
            symbolBooks.processUpdate(symbol, bidUpdate, askUpdate);
        });
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Benchmark completed in " << elapsed.count() << " seconds." << std::endl;

    //symbolBooks.printBestBidAsk();
}

int main()
{
    benchmarkMultipleSymbols(2'000, 2'000);

	return 0;
}
