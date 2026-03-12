cmake_minimum_required(VERSION 4.0)
project(GameLab)

set(CMAKE_CXX_STANDARD 23)

option(BUILD_TESTS "Build tests" ON)

add_executable(GameLab main.cpp
        src/GameEngine.cpp
        src/Player.cpp
        src/Screen.cpp
        src/Random.cpp
        src/Entity.cpp
        src/Item.cpp
        src/Event.cpp
        src/Room.cpp
        src/Dungeon.cpp
)

target_include_directories(GameLab PRIVATE include)

include(FetchContent)
FetchContent_Declare(
        google_test
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(google_test)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()