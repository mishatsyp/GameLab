cmake_minimum_required(VERSION 4.0)
project(GameLab)

set(CMAKE_CXX_STANDARD 23)

add_executable(GameLab main.cpp
        include/GameEngine.h
        src/GameEngine.cpp
        include/Player.h
        src/Player.cpp
        include/Screen.h
        src/Screen.cpp
        include/Random.h
        src/Random.cpp
        include/Entity.h
        src/Entity.cpp
        include/Item.h
        src/Item.cpp
        include/Event.h
        src/Event.cpp
        include/Room.h
        src/Room.cpp
)