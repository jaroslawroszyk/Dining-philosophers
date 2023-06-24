#pragma once
#include <mutex>
#include <condition_variable>

namespace DiningPhilosophers
{
    class Semaphore
    {
    public:
        Semaphore(int = 1);

        void notify();
        void wait();

    private:
        std::mutex mutex_;
        std::condition_variable cv_;
        int count_;
    };
} //namespace DiningPhilosophers
