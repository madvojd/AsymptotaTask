#include <iostream>
#include <string>

#include "Book.h"

void OrderBook::updateBid(double price, double quantity)
{
    std::unique_lock<std::shared_mutex> lock(_bookMutex);
    if (quantity == 0) {
        _bids.erase(price);
    }
    else {
        _bids[price] = quantity;
    }
}

void OrderBook::updateAsk(double price, double quantity)
{
    std::unique_lock<std::shared_mutex> lock(_bookMutex);
    if (quantity == 0) {
        _asks.erase(price);
    }
    else {
        _asks[price] = quantity;
    }
}

double OrderBook::bestBid()
{
    std::shared_lock<std::shared_mutex> lock(_bookMutex);
    return _bids.empty() ? 0.0 : _bids.begin()->first;
}

double OrderBook::bestAsk()
{
    std::shared_lock<std::shared_mutex> lock(_bookMutex);
    return _asks.empty() ? 0.0 : _asks.begin()->first;
}

void OrderBook::print()
{
    std::shared_lock<std::shared_mutex> lock(_bookMutex);
    std::cout << "Bids:" << std::endl;
    for (const auto& [price, qty] : _bids) {
        std::cout << price << " : " << qty << std::endl;
    }

    std::cout << "Asks:" << std::endl;
    for (const auto& [price, qty] : _asks) {
        std::cout << price << " : " << qty << std::endl;
    }
}

void OrderBook::applyUpdate(const std::vector<std::pair<double, double>>& bidUpdate, const std::vector<std::pair<double, double>>& askUpdate)
{
    for (const auto& [price, qty] : bidUpdate) {
        updateBid(price, qty);
    }
    for (const auto& [price, qty] : askUpdate) {
        updateAsk(price, qty);
    }
}
