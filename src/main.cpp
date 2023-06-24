#include <thread>
#include <vector>
#include "../include/Philosopher.hpp"
#include "../include/Semaphore.hpp"
#include "../include/Chopstick.hpp"
#include "../include/Utils.hpp"

int main()
{
    std::vector<Philosopher> philosophers;
    DiningPhilosophers::Semaphore waiter(Utils::NUM_PHILOSOPHERS - 1);

    std::vector<DiningPhilosophers::Chopstick> chopsticks(Utils::NUM_PHILOSOPHERS);
    for (int i = 0; i < Utils::NUM_PHILOSOPHERS; i++)
    {
        philosophers.emplace_back(i, &chopsticks[i], &chopsticks[(i + 1) % Utils::NUM_PHILOSOPHERS], &waiter);
    }

    std::vector<std::thread> threads;
    for (int i = 0; i < Utils::NUM_PHILOSOPHERS; i++)
    {
        threads.emplace_back(&Philosopher::dine, &philosophers[i]);
    }

    while (true)
    {
        // system("clear");
        Utils::clearScreen();
        Utils::printTable(philosophers);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    for (auto& thread : threads)
    {
        thread.join();
    }

    return 0;
}
