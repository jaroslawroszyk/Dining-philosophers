cmake_minimum_required(VERSION 3.20..3.26.3)
project(DinningPhilosophers)
set(CMAKE_CXX_STANDARD 20)

set(HEADERS
    include/Chopstick.hpp
    include/Philosopher.hpp
    include/Utils.hpp
    include/Semaphore.hpp
        )

set(SOURCES
    src/Chopstick.cpp
    src/Utils.cpp
    src/Philosopher.cpp
    )

set(FLAGS)
#  -Wall -Wextra -Wpedantic)

add_executable(${PROJECT_NAME} ${SOURCES} src/main.cpp)
target_compile_options(${PROJECT_NAME} PUBLIC ${FLAGS})
