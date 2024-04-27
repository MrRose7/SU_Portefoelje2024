cmake_minimum_required(VERSION 3.5)

project(src_SU_Portefoelje LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5Sql REQUIRED)

add_executable(src_SU_Portefoelje main.cpp hero.h enemy.h DBFetch.h game.h)
target_link_libraries(src_SU_Portefoelje  Qt5::Core Qt5::Sql)
