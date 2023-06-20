cmake_minimum_required(VERSION 3.20..3.26.3)
project(studentDb)
set(CMAKE_CXX_STANDARD 20)

set(HEADERS
    include/
        )

set(SOURCES
    src/
    )

set(FLAGS)
#  -Wall -Wextra -Wpedantic)

add_executable(${PROJECT_NAME} ${SOURCES} src/main.cpp src/database.cpp src/student.cpp)
target_compile_options(${PROJECT_NAME} PUBLIC ${FLAGS})
