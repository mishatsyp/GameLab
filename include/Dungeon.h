#ifndef DUNGEON_H
#define DUNGEON_H
#include <iostream>
#include <vector>
#include <memory>
#include <utility>
#include "Room.h"
#include "Random.h"

class Dungeon {
private:
    std::vector<std::vector<int>> matrix;  // матрица подземелья
    std::pair<int, int> currentRoomIndex;  // позиция игрока (x, y)

    // Паттерн + его стартовые координаты
    struct PatternData {
        std::vector<std::vector<int>> layout;
        std::pair<int, int> startPos;
    };

    std::vector<PatternData> patterns;

    static constexpr int MIN_ROOMS = 5;
    static constexpr int MAX_ROOMS = 10;

public:
    explicit Dungeon();  // конструктор сразу выбирает рандомный паттерн

    Dungeon(const Dungeon&) = delete;
    Dungeon& operator=(const Dungeon&) = delete;
    Dungeon(Dungeon&&) noexcept = default;
    Dungeon& operator=(Dungeon&&) noexcept = default;

    // Движение
    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();

    // Геттеры
    int getCurrentX() const { return currentRoomIndex.first; }
    int getCurrentY() const { return currentRoomIndex.second; }
    int getCell(int x, int y) const;  // получить значение в клетке
    size_t getRoomCount() const;
};

#endif // DUNGEON_H