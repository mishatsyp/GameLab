cmake_minimum_required(VERSION 4.0)
project(GameLab)

set(CMAKE_CXX_STANDARD 23)

add_executable(GameLab main.cpp
        src/GameEngine.cpp
        src/Player.cpp
        src/Screen.cpp
        src/Random.cpp
        src/Entity.cpp
        src/Item.cpp
        src/Dungeon.cpp
        src/Event.cpp
        src/Room.cpp)