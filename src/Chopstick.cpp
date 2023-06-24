#include "../include/Chopstick.hpp"
#include <mutex>

using namespace DiningPhilosophers;

Chopstick::Chopstick(int id) : id(id) {}
Chopstick::Chopstick() : id(0) {}

void Chopstick::pickUp()
{
    mutex.lock();
    id++;
}

void Chopstick::putDown()
{
    mutex.unlock();
}

int Chopstick::getId() const { return id; }
