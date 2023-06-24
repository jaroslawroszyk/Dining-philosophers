#pragma once
#include "Philosopher.hpp"
#include <vector>
#include <filesystem>

namespace Utils
{
    constexpr int NUM_OF_PHILOSOPHERS = 5;

    void clearScreen();
    void printTable(const std::vector<Philosopher>&);
} // namespace Utils
