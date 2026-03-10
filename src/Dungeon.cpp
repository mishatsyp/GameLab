#include "../include/Dungeon.h"
Dungeon::Dungeon(Player& p) {
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

    // Генерируем комнаты на основе матрицы
    generateRooms(p);
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

void Dungeon::generateRooms(Player& p) {
    rooms_.clear();

    // Проходим по всей матрице и создаем комнаты
    for (size_t y = 0; y < matrix.size(); ++y) {
        for (size_t x = 0; x < matrix[y].size(); ++x) {
            int cellValue = matrix[y][x];

            if (cellValue > 0) { // Если это комната (1) или выход (2)
                Room::RoomType type;

                if (cellValue == 2) {
                    // Выход - всегда комната с монстром
                    type = Room::RoomType::MONSTER;
                } else {
                    // Обычная комната (значение 1) - может быть пустой или с ивентом
                    // В конструкторе Room тип EMPTY, но generateRoomContent сам решит,
                    // станет ли она EVENT (с вероятностью 70%)
                    type = Room::RoomType::EMPTY;
                }

                // Создаем комнату
                Room room(type, p);
                room.setCoordinates(static_cast<int>(x), static_cast<int>(y));
                rooms_.push_back(std::move(room));
            }
        }
    }
}

Room* Dungeon::getRoomAt(int x, int y) {
    // Проверяем, что координаты в пределах матрицы
    if (y >= 0 && y < static_cast<int>(matrix.size()) &&
        x >= 0 && x < static_cast<int>(matrix[0].size())) {

        // Если в матрице по этим координатам стена (0) - комнаты нет
        if (matrix[y][x] == 0) {
            return nullptr;
        }

        // Ищем комнату с такими координатами в векторе
        for (auto& room : rooms_) {
            auto coords = room.getCoordinates();
            if (coords.first == x && coords.second == y) {
                return &room;
            }
        }
    }
    return nullptr;
}

const Room* Dungeon::getRoomAt(int x, int y) const {
    // Аналогично const версии
    if (y >= 0 && y < static_cast<int>(matrix.size()) &&
        x >= 0 && x < static_cast<int>(matrix[0].size())) {

        if (matrix[y][x] == 0) {
            return nullptr;
        }

        for (const auto& room : rooms_) {
            auto coords = room.getCoordinates();
            if (coords.first == x && coords.second == y) {
                return &room;
            }
        }
    }
    return nullptr;
}