#include "../include/Philosopher.hpp"
#include "../include/Chopstick.hpp"
#include "../include/Semaphore.hpp"
#include <iostream>
#include <thread>

Philosopher::Philosopher(int id, DiningPhilosophers::Chopstick* left_chopstick, DiningPhilosophers::Chopstick* right_chopstick, DiningPhilosophers::Semaphore* waiter, int eatingCount)
    : id(id), leftChopstick(left_chopstick), rightChopstick(right_chopstick), waiter(waiter), status("Thinking"), eatingCount(eatingCount)
{
}

void Philosopher::dine()
{
    while (true)
    {
        std::cout << "Philosopher " << id << " is " << status << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));

        if (status == "Thinking")
        {
            waiter->wait();
            leftChopstick->pickUp(id);
            rightChopstick->pickUp(id);
            eatingCount++;
            status = "Eating";
        }
        else if (status == "Eating")
        {
            leftChopstick->putDown();
            rightChopstick->putDown();
            waiter->notify();
            status = "Waiting";
        }
        else if (status == "Waiting")
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            status = "Thinking";
        }
    }
}

int Philosopher::getId() const { return id; }
const std::string& Philosopher::getStatus() const { return status; }
int Philosopher::getEatingCount() const { return eatingCount; }
DiningPhilosophers::Chopstick* Philosopher::getLeftChopstick() const { return leftChopstick; }
DiningPhilosophers::Chopstick* Philosopher::getRightChopstick() const { return rightChopstick; }


