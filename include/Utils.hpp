#pragma once
#include "Philosopher.hpp"
#include <vector>
#include <filesystem>

namespace DiningPhilosophers
{
    class Philosopher;
    // class Chopstick;
} // 
namespace Utils
{
    constexpr int NUM_PHILOSOPHERS = 5;

    void clearScreen();
    void printTable(const std::vector<Philosopher>&);
} // namespace Utils
