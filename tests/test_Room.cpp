#include <gtest/gtest.h>
#include "../include/Room.h"
#include "../include/Player.h"
#include "../include/Event.h"

TEST(RoomTest, Constructor) {
    Player player("TestPlayer");
    const Room room(Room::RoomType::EMPTY, player);

    EXPECT_FALSE(room.getisExplored());
}

TEST(RoomTest, ConstructorEventRoom) {
    Player player("TestPlayer");
    const Room room(Room::RoomType::EVENT, player);

    EXPECT_EQ(room.getType(), Room::RoomType::EVENT);
    EXPECT_FALSE(room.getisExplored());
}

TEST(RoomTest, ConstructorExitRoom) {
    Player player("TestPlayer");
    const Room room(Room::RoomType::EXIT, player);

    EXPECT_EQ(room.getType(), Room::RoomType::EXIT);
    EXPECT_FALSE(room.getisExplored());
}

TEST(RoomTest, SetCoordinates) {
    Player player("TestPlayer");
    Room room(Room::RoomType::EMPTY, player);

    room.setCoordinates(3, 2);

    EXPECT_EQ(room.getCoordinates().first, 3);
    EXPECT_EQ(room.getCoordinates().second, 2);
}

TEST(RoomTest, GetEventFromEventRoom) {
    Player player("TestPlayer");
    const Room room(Room::RoomType::EVENT, player);
    const auto event = room.GetEvent();
    EXPECT_TRUE(event.has_value());
}

TEST(RoomTest, MoveConstructor) {
    Player player("TestPlayer");
    Room original(Room::RoomType::EVENT, player);
    original.setCoordinates(1, 2);
    const Room moved = std::move(original);
    EXPECT_EQ(moved.getCoordinates().first, 1);
    EXPECT_EQ(moved.getCoordinates().second, 2);
    EXPECT_EQ(moved.getType(), Room::RoomType::EVENT);
}

TEST(RoomTest, MoveAssignment) {
    Player player("TestPlayer");
    Room original(Room::RoomType::EVENT, player);
    original.setCoordinates(2, 4);

    Room target(Room::RoomType::EMPTY, player);
    target = std::move(original);

    EXPECT_EQ(target.getCoordinates().first, 2);
    EXPECT_EQ(target.getCoordinates().second, 4);
    EXPECT_EQ(target.getType(), Room::RoomType::EVENT);
}