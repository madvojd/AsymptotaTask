
#include "gtest/gtest.h"
#include "../AsymptotaTest/book.h"

TEST(OrderBookTest, InitialSnapshot) {
    OrderBook book;

    // Initialize with snapshot
    std::vector<std::pair<double, double>> bid_snapshot = {
        {0.0024, 14.7}, {0.0022, 6.4}, {0.0020, 9.7}
    };
    std::vector<std::pair<double, double>> ask_snapshot = {
        {0.0024, 14.9}, {0.0026, 3.6}, {0.0028, 1.0}
    };

    book.applyUpdate(bid_snapshot, ask_snapshot);

    // Check best bid and ask prices
    ASSERT_DOUBLE_EQ(book.bestBid(), 0.0024);
    ASSERT_DOUBLE_EQ(book.bestAsk(), 0.0024);
}

TEST(OrderBookTest, ApplyUpdate) {
    OrderBook book;

    // Initialize with snapshot
    std::vector<std::pair<double, double>> bid_snapshot = {
        {0.0024, 14.7}, {0.0022, 6.4}, {0.0020, 9.7}
    };
    std::vector<std::pair<double, double>> ask_snapshot = {
        {0.0024, 14.9}, {0.0026, 3.6}, {0.0028, 1.0}
    };

    book.applyUpdate(bid_snapshot, ask_snapshot);

    // Apply updates
    std::vector<std::pair<double, double>> bid_update = { {0.0024, 10.0} };
    std::vector<std::pair<double, double>> ask_update = { {0.0026, 100.0} };

    book.applyUpdate(bid_update, ask_update);

    // Check updated bid and ask
    ASSERT_DOUBLE_EQ(book._bids[0.0024], 10.0);
    ASSERT_DOUBLE_EQ(book._asks[0.0026], 100.0);
}

TEST(OrderBookTest, RemoveLevelOnZeroQuantity) {
    OrderBook book;

    // Initialize with snapshot
    std::vector<std::pair<double, double>> bid_snapshot = {
        {0.0024, 14.7}, {0.0022, 6.4}, {0.0020, 9.7}
    };
    std::vector<std::pair<double, double>> ask_snapshot = {
        {0.0024, 14.9}, {0.0026, 3.6}, {0.0028, 1.0}
    };

    book.applyUpdate(bid_snapshot, ask_snapshot);

    // Apply updates: remove bids and asks
    std::vector<std::pair<double, double>> bid_update = { {0.0024, 0.0} };
    std::vector<std::pair<double, double>> ask_update = { {0.0026, 0.0} };

    book.applyUpdate(bid_update, ask_update);

    // Check that price levels are removed
    ASSERT_EQ(book._bids.find(0.0024), book._bids.end());
    ASSERT_EQ(book._asks.find(0.0026), book._asks.end());
}