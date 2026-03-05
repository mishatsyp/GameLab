cmake_minimum_required(VERSION 4.0)
project(GameLab)

set(CMAKE_CXX_STANDARD 23)

add_executable(GameLab main.cpp
        include/GameEngine.h
        include/Player.h
        include/Room.h
        include/Item.h
        include/Event.h
        include/Entity.h
        include/Random.h
        include/Screen.h
        src/GameEngine.cpp
        src/Player.cpp
        src/Screen.cpp
        src/Random.cpp)