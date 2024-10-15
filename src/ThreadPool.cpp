#include "ThreadPool.h"

// Thread pool constructor
ThreadPool::ThreadPool(size_t threads) : _stop(false) {
    for (size_t i = 0; i < threads; ++i) {
        _workers.emplace_back([this] {
            while (true) {
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock(this->_queueMutex);
                    this->_condition.wait(lock, [this] { return this->_stop || !this->_tasks.empty(); });
                    if (this->_stop && this->_tasks.empty()) return;
                    task = std::move(this->_tasks.front());
                    this->_tasks.pop();
                }
                task();
            }
            });
    }
}

// Enqueue new task in the pool
void ThreadPool::enqueue(std::function<void()> task) {
    {
        std::lock_guard<std::mutex> lock(_queueMutex);
        _tasks.push(std::move(task));
    }
    _condition.notify_one();
}

// Destructor to stop threads
ThreadPool::~ThreadPool() {
    {
        std::lock_guard<std::mutex> lock(_queueMutex);
        _stop = true;
    }
    _condition.notify_all();
    for (std::thread& worker : _workers)
        worker.join();
}