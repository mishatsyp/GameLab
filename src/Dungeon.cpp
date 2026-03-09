#include "../include/Dungeon.h"
Dungeon::Dungeon() {
    // Инициализируем паттерны прямо здесь
    patterns = {
        // Паттерн 1: Змейка (старт в 1)
        {
            {
                {1, 0, 0, 0},
                {1, 1, 1, 0},
                {0, 0, 1, 0},
                {0, 0, 1, 2}
            },
            {0, 0}
        },
        // Паттерн 2: Крест
        {
            {
                {0, 1, 0, 0},
                {1, 1, 1, 0},
                {0, 1, 0, 0},
                {0, 1, 1, 2}
            },
            {1, 0}
        },
        // Паттерн 3: Две ветки
        {
            {
                {1, 1, 0, 0},
                {0, 1, 1, 0},
                {0, 0, 1, 0},
                {0, 0, 1, 2}
            },
            {0, 0}
        },
        // Паттерн 4: Комнаты
        {
            {
                {1, 1, 0, 1},
                {0, 1, 1, 1},
                {0, 0, 0, 1},
                {0, 0, 0, 2}
            },
            {0, 0}
        },
        // Паттерн 5: Т-образный
        {
            {
                {1, 1, 1, 0},
                {0, 1, 0, 0},
                {0, 1, 0, 0},
                {0, 1, 1, 2}
            },
            {0, 0}
        },
        // Паттерн 6: Лабиринт
        {
            {
                {1, 1, 0, 1},
                {0, 1, 0, 1},
                {0, 1, 1, 1},
                {0, 0, 0, 2}
            },
            {0, 0}
        },
        // Паттерн 7: Прямая
        {
            {
                {1, 0, 0, 0},
                {1, 0, 0, 0},
                {1, 0, 0, 0},
                {1, 1, 1, 2}
            },
            {0, 0}
        },
        // Паттерн 8: Квадрат
        {
            {
                {1, 1, 0, 0},
                {1, 0, 0, 0},
                {1, 0, 0, 0},
                {1, 1, 1, 2}
            },
            {0, 0}
        }
    };
    
    // Выбираем рандомный паттерн
    Random& rng = Random::getInstance();
    int patternIndex = rng.getInt(0, static_cast<int>(patterns.size()) - 1);
    
    matrix = patterns[patternIndex].layout;
    currentRoomIndex = patterns[patternIndex].startPos;
}

void Dungeon::moveRight() {
    currentRoomIndex.first++;
}

void Dungeon::moveLeft() {
    currentRoomIndex.first--;
}

void Dungeon::moveUp() {
    currentRoomIndex.second--;
}

void Dungeon::moveDown() {
    currentRoomIndex.second++;
}

int Dungeon::getCell(int x, int y) const {
    if (y >= 0 && y < static_cast<int>(matrix.size()) &&
        x >= 0 && x < static_cast<int>(matrix[0].size())) {
        return matrix[y][x];
    }
    return 0;
}

size_t Dungeon::getRoomCount() const {
    size_t count = 0;
    for (const auto& row : matrix) {
        for (int cell : row) {
            if (cell > 0) count++;
        }
    }
    return count;
}