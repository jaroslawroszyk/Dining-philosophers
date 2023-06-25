#pragma once
#include <mutex>

namespace DiningPhilosophers
{
    class Chopstick
    {
    public:
        Chopstick(int id);
        Chopstick();

        void pickUp(int);

        void putDown();

        int getId() const;

    private:
        int id;
        std::mutex mutex;
    };
} // namespace DiningPhilosophers