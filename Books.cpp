#include <iostream>
#include "Books.h"

void books::processUpdate(const std::string& symbol, const std::vector<std::pair<double, double>>& bidUpdate, const std::vector<std::pair<double, double>>& askUpdate)
{
    std::unique_lock<std::shared_mutex> lock(orderBooksMutex);

    // Look up the order book for the given symbol or create it if it doesn't exist
    auto& book = orderBooks[symbol];

    // Apply the diff (update bids and asks)
    book.applyUpdate(bidUpdate, askUpdate);
}

void books::printBestBidAsk()
{
    std::shared_lock<std::shared_mutex> lock(orderBooksMutex);

    for (auto& [symbol, book] : orderBooks) {
        double bestBid = book.bestBid();
        double bestAsk = book.bestAsk();

        std::cout << "Symbol: " << symbol << "\n";
        std::cout << "Best Bid: " << bestBid << ", Best Ask: " << bestAsk << "\n\n";
    }
}
