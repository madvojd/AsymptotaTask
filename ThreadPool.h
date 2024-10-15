#pragma once

#include <thread>
#include <queue>
#include <condition_variable>
#include <functional>

// A simple thread pool
class ThreadPool {
    std::vector<std::thread> _workers;
    std::queue<std::function<void()>> _tasks;
    std::mutex _queueMutex;
    std::condition_variable _condition;
    bool _stop;

public:
    ThreadPool(size_t threads);
    ~ThreadPool();
    void enqueue(std::function<void()> task);
};

