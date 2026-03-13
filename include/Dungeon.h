#ifndef DUNGEON_H
#define DUNGEON_H
#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <utility>
#include "Random.h"
#include "Player.h"
#include "Room.h"
#include "Event.h"

class Dungeon {
private:
    std::vector<std::vector<int>> matrix;
    std::pair<int, int> currentRoomIndex;
    std::vector<Room> rooms_;

    struct PatternData {
        std::vector<std::vector<int>> layout;
        std::pair<int, int> startPos;
    };

    std::vector<PatternData> patterns;

    static constexpr int MIN_ROOMS = 5;
    static constexpr int MAX_ROOMS = 10;

public:
    explicit Dungeon(Player& p);

    Dungeon(const Dungeon&) = delete;
    Dungeon& operator=(const Dungeon&) = delete;
    Dungeon(Dungeon&&) noexcept = default;
    Dungeon& operator=(Dungeon&&) noexcept = default;

    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();

    int getCurrentX() const { return currentRoomIndex.first; }
    int getCurrentY() const { return currentRoomIndex.second; }
    int getCell(int x, int y) const;
    size_t getRoomCount() const;

    void generateRooms(Player& player);
    Room* getRoomAt(int x, int y);
    const Room* getRoomAt(int x, int y) const;
};

#endif // DUNGEON_H