#include "../include/Chopstick.hpp"
#include <mutex>

DiningPhilosophers::Chopstick::Chopstick(int id) : id(id) {}
DiningPhilosophers::Chopstick::Chopstick() : id(0) {}

void DiningPhilosophers::Chopstick::pickUp()
{
    mutex.lock();
    id++;
}

void DiningPhilosophers::Chopstick::putDown()
{
    mutex.unlock();
    id--;
}

int DiningPhilosophers::Chopstick::getId() const { return id; }
