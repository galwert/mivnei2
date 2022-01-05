cmake_minimum_required(VERSION 3.16)
project(wet2)

set(CMAKE_CXX_STANDARD 14)

add_executable(wet2 main.cpp RankTree.cpp RankTree.h DynamicArray.cpp DynamicArray.h Group.h Group.cpp Player.h Player.cpp
        UnionFind.h PlayersManager.cpp PlayersManager.h)