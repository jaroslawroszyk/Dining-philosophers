#include "../include/Semaphore.hpp"
#include <mutex>
#include <condition_variable>

using namespace DiningPhilosophers;

Semaphore::Semaphore(int count) : count_(count) {}

void Semaphore::notify()
{
    std::unique_lock<std::mutex> lock(mutex_);
    count_++;
    cv_.notify_one();
}

void Semaphore::wait()
{
    std::unique_lock<std::mutex> lock(mutex_);
    while (count_ == 0)
    {
        cv_.wait(lock);
    }
    count_--;
}

