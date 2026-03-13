#include <gtest/gtest.h>
#include "../include/Dungeon.h"
#include "../include/Player.h"

TEST(DungeonTest, Constructor) {
    Player player("TestPlayer");
    const Dungeon dungeon(player);

    EXPECT_GT(dungeon.getRoomCount(), 0);
}

TEST(DungeonTest, GetCurrentCoordinates) {
    Player player("TestPlayer");
    const Dungeon dungeon(player);

    const int x = dungeon.getCurrentX();
    const int y = dungeon.getCurrentY();

    EXPECT_GE(x, 0);
    EXPECT_GE(y, 0);
    EXPECT_LT(x, 4);
    EXPECT_LT(y, 4);
}

TEST(DungeonTest, GetCell) {
    Player player("TestPlayer");
    const Dungeon dungeon(player);

    const int x = dungeon.getCurrentX();
    const int y = dungeon.getCurrentY();

    EXPECT_GT(dungeon.getCell(x, y), 0);
    EXPECT_EQ(dungeon.getCell(-1, -1), 0);
    EXPECT_EQ(dungeon.getCell(10, 10), 0);
}

TEST(DungeonTest, MoveRight) {
    Player player("TestPlayer");
    Dungeon dungeon(player);

    const int x = dungeon.getCurrentX();
    const int y = dungeon.getCurrentY();

    dungeon.moveRight();
    EXPECT_EQ(dungeon.getCurrentX(), x + 1);
    EXPECT_EQ(dungeon.getCurrentY(), y);
}

TEST(DungeonTest, MoveLeft) {
    Player player("TestPlayer");
    Dungeon dungeon(player);

    const int x = dungeon.getCurrentX();
    const int y = dungeon.getCurrentY();

    dungeon.moveLeft();
    EXPECT_EQ(dungeon.getCurrentX(), x - 1);
    EXPECT_EQ(dungeon.getCurrentY(), y);
}

TEST(DungeonTest, MoveDown) {
    Player player("TestPlayer");
    Dungeon dungeon(player);

    const int x = dungeon.getCurrentX();
    const int y = dungeon.getCurrentY();

    dungeon.moveDown();
    EXPECT_EQ(dungeon.getCurrentX(), x);
    EXPECT_EQ(dungeon.getCurrentY(), y + 1);
}

TEST(DungeonTest, MoveUp) {
    Player player("TestPlayer");
    Dungeon dungeon(player);

    const int x = dungeon.getCurrentX();
    const int y = dungeon.getCurrentY();

    dungeon.moveUp();
    EXPECT_EQ(dungeon.getCurrentX(), x);
    EXPECT_EQ(dungeon.getCurrentY(), y - 1);
}

TEST(DungeonTest, GetRoomAt) {
    Player player("TestPlayer");
    Dungeon dungeon(player);

    const int x = dungeon.getCurrentX();
    const int y = dungeon.getCurrentY();

    Room* room = dungeon.getRoomAt(x, y);
    ASSERT_NE(room, nullptr);
    EXPECT_EQ(room->getCoordinates().first, x);
    EXPECT_EQ(room->getCoordinates().second, y);
}

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

TEST(DungeonTest, RoomCount) {
    Player player("TestPlayer");
    const Dungeon dungeon(player);

    const size_t roomCount = dungeon.getRoomCount();

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

TEST(DungeonTest, MoveConstructor) {
    Player player("TestPlayer");
    Dungeon original(player);

    const int x = original.getCurrentX();
    const int y = original.getCurrentY();
    const size_t count = original.getRoomCount();

    const Dungeon moved = std::move(original);
    EXPECT_EQ(moved.getCurrentX(), x);
    EXPECT_EQ(moved.getCurrentY(), y);
    EXPECT_EQ(moved.getRoomCount(), count);
}