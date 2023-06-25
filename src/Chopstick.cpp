#include "../include/Chopstick.hpp"
#include <mutex>

DiningPhilosophers::Chopstick::Chopstick(int id) : id(id) {}
DiningPhilosophers::Chopstick::Chopstick() : id(0) {}

void DiningPhilosophers::Chopstick::pickUp(int p_id)
{
    mutex.lock();
    id = p_id;
}

void DiningPhilosophers::Chopstick::putDown()
{
    id = -1;
    mutex.unlock();
}

int DiningPhilosophers::Chopstick::getId() const { return id; }
