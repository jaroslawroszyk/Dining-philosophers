#pragma once
#include <string>

namespace DiningPhilosophers
{
    class Semaphore;
    class Chopstick;
} // namespace DiningPhilosophers

class Philosopher
{
public:
    Philosopher(int, DiningPhilosophers::Chopstick*, DiningPhilosophers::Chopstick*, DiningPhilosophers::Semaphore*, int = 0);

    void dine();

    int getId() const;
    const std::string& getStatus() const;
    int getEatingCount() const;
    DiningPhilosophers::Chopstick* getLeftChopstick() const;
    DiningPhilosophers::Chopstick* getRightChopstick() const;

private:
    int id;
    DiningPhilosophers::Chopstick* leftChopstick;
    DiningPhilosophers::Chopstick* rightChopstick;
    DiningPhilosophers::Semaphore* waiter;
    std::string status;
    int eatingCount;
};
