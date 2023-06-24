#include "../include/Utils.hpp"
#include "../include/Chopstick.hpp"
#include "../include/Philosopher.hpp"
#include <iostream>
#include <iomanip>
#include <vector>

void Utils::clearScreen()
{
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

void Utils::printTable(const std::vector<Philosopher>& philosophers)
{
    std::cout << "--------------------------------------------------------------" << std::endl;
    std::cout << "| Id Ph| Status     | Left  Fork | Right Fork |  Count |" << std::endl;
    std::cout << "--------------------------------------------------------------" << std::endl;

    for (const auto& philosopher : philosophers)
    {
        std::cout << "| " << std::setw(5) << philosopher.getId() << " | ";
        std::cout << std::setw(10) << philosopher.getStatus() << " |";
        std::cout << std::setw(11) << philosopher.getLeftChopstick()->getId() << " |";
        std::cout << std::setw(12) << philosopher.getRightChopstick()->getId() << " |";
        std::cout << std::setw(7) << philosopher.getEatingCount() << " |";

        std::cout << std::endl;
    }

    std::cout << "--------------------------------------------------------------" << std::endl;
}
