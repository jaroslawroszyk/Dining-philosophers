#pragma once
#include <mutex>

namespace DiningPhilosophers
{
    class Chopstick
    {
    public:
        Chopstick(int id);
        Chopstick();

        void pickUp();

        void putDown();

        int getId() const;

    private:
        int id;
        std::mutex mutex;
    };
} // namespace DiningPhilosophers