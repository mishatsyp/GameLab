#include <gtest/gtest.h>
#include "../include/Dungeon.h"
#include "../include/Player.h"

// Тест конструктора подземелья
TEST(DungeonTest, Constructor) {
    Player player("TestPlayer");
    Dungeon dungeon(player);

    EXPECT_GT(dungeon.getRoomCount(), 0);
}

// Тест получения координат
TEST(DungeonTest, GetCurrentCoordinates) {
    Player player("TestPlayer");
    Dungeon dungeon(player);

    int x = dungeon.getCurrentX();
    int y = dungeon.getCurrentY();

    EXPECT_GE(x, 0);
    EXPECT_GE(y, 0);
    EXPECT_LT(x, 4);
    EXPECT_LT(y, 4);
}

// Тест получения значения ячейки
TEST(DungeonTest, GetCell) {
    Player player("TestPlayer");
    Dungeon dungeon(player);

    int x = dungeon.getCurrentX();
    int y = dungeon.getCurrentY();

    EXPECT_GT(dungeon.getCell(x, y), 0);
    EXPECT_EQ(dungeon.getCell(-1, -1), 0);
    EXPECT_EQ(dungeon.getCell(10, 10), 0);
}

// Тест перемещения вправо
TEST(DungeonTest, MoveRight) {
    Player player("TestPlayer");
    Dungeon dungeon(player);

    int x = dungeon.getCurrentX();
    int y = dungeon.getCurrentY();

    dungeon.moveRight();
    EXPECT_EQ(dungeon.getCurrentX(), x + 1);
    EXPECT_EQ(dungeon.getCurrentY(), y);
}

// Тест перемещения влево
TEST(DungeonTest, MoveLeft) {
    Player player("TestPlayer");
    Dungeon dungeon(player);

    int x = dungeon.getCurrentX();
    int y = dungeon.getCurrentY();

    dungeon.moveLeft();
    EXPECT_EQ(dungeon.getCurrentX(), x - 1);
    EXPECT_EQ(dungeon.getCurrentY(), y);
}

// Тест перемещения вниз
TEST(DungeonTest, MoveDown) {
    Player player("TestPlayer");
    Dungeon dungeon(player);

    int x = dungeon.getCurrentX();
    int y = dungeon.getCurrentY();

    dungeon.moveDown();
    EXPECT_EQ(dungeon.getCurrentX(), x);
    EXPECT_EQ(dungeon.getCurrentY(), y + 1);
}

// Тест перемещения вверх
TEST(DungeonTest, MoveUp) {
    Player player("TestPlayer");
    Dungeon dungeon(player);

    int x = dungeon.getCurrentX();
    int y = dungeon.getCurrentY();

    dungeon.moveUp();
    EXPECT_EQ(dungeon.getCurrentX(), x);
    EXPECT_EQ(dungeon.getCurrentY(), y - 1);
}

// Тест получения комнаты
TEST(DungeonTest, GetRoomAt) {
    Player player("TestPlayer");
    Dungeon dungeon(player);

    int x = dungeon.getCurrentX();
    int y = dungeon.getCurrentY();

    Room* room = dungeon.getRoomAt(x, y);
    ASSERT_NE(room, nullptr);
    EXPECT_EQ(room->getCoordinates().first, x);
    EXPECT_EQ(room->getCoordinates().second, y);
}

// Тест получения комнаты в стене
TEST(DungeonTest, GetRoomAtWall) {
    Player player("TestPlayer");
    Dungeon dungeon(player);

    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (dungeon.getCell(x, y) == 0) {
                EXPECT_EQ(dungeon.getRoomAt(x, y), nullptr);
                return;
            }
        }
    }
}

// Тест наличия выхода
TEST(DungeonTest, HasExit) {
    Player player("TestPlayer");
    Dungeon dungeon(player);

    bool foundExit = false;
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (dungeon.getCell(x, y) == 2) {
                foundExit = true;
                Room* exitRoom = dungeon.getRoomAt(x, y);
                ASSERT_NE(exitRoom, nullptr);
                EXPECT_EQ(exitRoom->getType(), Room::RoomType::EXIT);
                break;
            }
        }
    }
    EXPECT_TRUE(foundExit);
}

// Тест подсчета комнат
TEST(DungeonTest, RoomCount) {
    Player player("TestPlayer");
    Dungeon dungeon(player);

    size_t roomCount = dungeon.getRoomCount();

    size_t manualCount = 0;
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (dungeon.getCell(x, y) > 0) {
                manualCount++;
            }
        }
    }

    EXPECT_EQ(roomCount, manualCount);
    EXPECT_GE(roomCount, 5);
    EXPECT_LE(roomCount, 10);
}

// Тест перемещения
TEST(DungeonTest, MoveConstructor) {
    Player player("TestPlayer");
    Dungeon original(player);

    int x = original.getCurrentX();
    int y = original.getCurrentY();
    size_t count = original.getRoomCount();

    Dungeon moved = std::move(original);
    EXPECT_EQ(moved.getCurrentX(), x);
    EXPECT_EQ(moved.getCurrentY(), y);
    EXPECT_EQ(moved.getRoomCount(), count);
}