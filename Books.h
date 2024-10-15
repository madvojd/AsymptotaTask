#pragma once

#include <unordered_map>
#include <string>
#include <shared_mutex>

#include "Book.h"

class books
{
public:

	// Function to process updates for a specific symbol
	void processUpdate(const std::string& symbol, const std::vector<std::pair<double, double>>& bidUpdate, const std::vector<std::pair<double, double>>& askUpdate);

	// Function to print the best bid and ask for each symbol
	void printBestBidAsk();

private:
	// Global storage for the order books keyed by symbol
	std::unordered_map<std::string, OrderBook> orderBooks;
	// Mutex for thread-safety
	std::shared_mutex  orderBooksMutex;
};

