#pragma once

#include <map>
#include <vector>
#include <shared_mutex>

class OrderBook {
public:
    // Function to update the book based on a price level
    void updateBid(double price, double quantity);

    void updateAsk(double price, double quantity);

    // Functions to get the best bid and ask prices
    double bestBid();
    // Update the ask price level
    double bestAsk();

    // For debugging purposes
    void print();

    // Function to apply an update (book diff) to the order book
    void applyUpdate(const std::vector<std::pair<double, double>>& bid_update, const std::vector<std::pair<double, double>>& ask_update);

//private:
    // Maps for storing bids and asks
    std::map<double, double, std::greater<double>> _bids;  // Bids in descending order, Bids: price -> quantity
    std::map<double, double> _asks;  // Asks in ascending order, Asks: price -> quantity

    // Mutex for thread-safe access to the order book
    std::shared_mutex _bookMutex;
};

