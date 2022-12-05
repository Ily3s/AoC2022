cmake_minimum_required(VERSION 3.23)
project(AoC2022 C)

set(CMAKE_C_STANDARD 11)

add_executable(AoC2022 src/main.c src/Common.h src/days/d1/day1.c src/days/d2/day2.c src/days/d3/day3.c src/days/d4/day4.c src/days/d5/day5.c)
