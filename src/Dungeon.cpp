#include "../include/Dungeon.h"
Dungeon::Dungeon(Player& p) {
    patterns = {
        {
            {
                {1, 0, 0, 0},
                {1, 1, 1, 0},
                {0, 0, 1, 0},
                {0, 0, 1, 2}
            },
            {0, 0}
        },
        {
            {
                {0, 1, 0, 0},
                {1, 1, 1, 0},
                {0, 1, 0, 0},
                {0, 1, 1, 2}
            },
            {1, 0}
        },
        {
            {
                {1, 1, 0, 0},
                {0, 1, 1, 0},
                {0, 0, 1, 0},
                {0, 0, 1, 2}
            },
            {0, 0}
        },
        {
            {
                {1, 1, 0, 1},
                {0, 1, 1, 1},
                {0, 0, 0, 1},
                {0, 0, 0, 2}
            },
            {0, 0}
        },
        {
            {
                {1, 1, 1, 0},
                {0, 1, 0, 0},
                {0, 1, 0, 0},
                {0, 1, 1, 2}
            },
            {0, 0}
        },
        {
            {
                {1, 1, 0, 1},
                {0, 1, 0, 1},
                {0, 1, 1, 1},
                {0, 0, 0, 2}
            },
            {0, 0}
        },
        {
            {
                {1, 0, 0, 0},
                {1, 0, 0, 0},
                {1, 0, 0, 0},
                {1, 1, 1, 2}
            },
            {0, 0}
        },
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
    
    Random& rng = Random::getInstance();
    const int patternIndex = rng.getInt(0, static_cast<int>(patterns.size()) - 1);
    
    matrix = patterns[patternIndex].layout;
    currentRoomIndex = patterns[patternIndex].startPos;

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
        for (const int cell : row) {
            if (cell > 0) count++;
        }
    }
    return count;
}

void Dungeon::generateRooms(Player& p) {
    rooms_.clear();

    for (size_t y = 0; y < matrix.size(); ++y) {
        for (size_t x = 0; x < matrix[y].size(); ++x) {
            int cellValue = matrix[y][x];

            if (cellValue > 0) {
                Room::RoomType type;

                if (cellValue == 2) {
                    type = Room::RoomType::EXIT;
                } else {
                    type = Room::RoomType::EMPTY;
                }

                Room room(type, p);
                room.setCoordinates(static_cast<int>(x), static_cast<int>(y));
                rooms_.push_back(std::move(room));
            }
        }
    }
}

Room* Dungeon::getRoomAt(int x, int y) {
    if (y >= 0 && y < static_cast<int>(matrix.size()) &&
        x >= 0 && x < static_cast<int>(matrix[0].size())) {

        if (matrix[y][x] == 0) {
            return nullptr;
        }

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