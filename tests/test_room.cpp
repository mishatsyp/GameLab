#include <gtest/gtest.h>
#include "../include/Room.h"
#include "../include/Player.h"
#include "../include/Event.h"

// Тест конструктора комнаты
TEST(RoomTest, Constructor) {
    Player player("TestPlayer");
    Room room(Room::RoomType::EMPTY, player);

    // Проверяем что тип установлен правильно
    EXPECT_EQ(room.getType(), Room::RoomType::EMPTY);
    // Проверяем что комната еще не исследована
    EXPECT_FALSE(room.getisExplored());
}

// Тест конструктора комнаты с типом EVENT
TEST(RoomTest, ConstructorEventRoom) {
    Player player("TestPlayer");
    Room room(Room::RoomType::EVENT, player);

    EXPECT_EQ(room.getType(), Room::RoomType::EVENT);
}

// Тест конструктора комнаты с типом EXIT
TEST(RoomTest, ConstructorExitRoom) {
    Player player("TestPlayer");
    Room room(Room::RoomType::EXIT, player);

    EXPECT_EQ(room.getType(), Room::RoomType::EXIT);
}

// Тест установки координат комнаты
TEST(RoomTest, SetCoordinates) {
    Player player("TestPlayer");
    Room room(Room::RoomType::EMPTY, player);

    room.setCoordinates(3, 2);

    // Проверяем что координаты сохранились
    EXPECT_EQ(room.getCoordinates().first, 3);
    EXPECT_EQ(room.getCoordinates().second, 2);
}

// Тест получения события из комнаты
TEST(RoomTest, GetEvent) {
    Player player("TestPlayer");
    Room room(Room::RoomType::EMPTY, player);

    // Для пустой комнаты событие должно отсутствовать
    EXPECT_FALSE(room.GetEvent().has_value());
}

// Тест получения события из комнаты с событием
TEST(RoomTest, GetEventFromEventRoom) {
    Player player("TestPlayer");
    Room room(Room::RoomType::EVENT, player);

    // Для комнаты с событием должен быть event
    auto event = room.GetEvent();
    // Проверяем что event существует
    EXPECT_TRUE(event.has_value());
}

// Тест конструктора перемещения
TEST(RoomTest, MoveConstructor) {
    Player player("TestPlayer");
    Room original(Room::RoomType::EMPTY, player);
    original.setCoordinates(1, 2); // Задаем координаты исходной комнате

    Room moved = std::move(original); // Перемещаем комнату

    // Проверяем что координаты переместились
    EXPECT_EQ(moved.getCoordinates().first, 1);
    EXPECT_EQ(moved.getCoordinates().second, 2);
    // Проверяем что тип сохранился
    EXPECT_EQ(moved.getType(), Room::RoomType::EMPTY);
}

// Тест оператора перемещения
TEST(RoomTest, MoveAssignment) {
    Player player("TestPlayer");
    Room original(Room::RoomType::EVENT, player);
    original.setCoordinates(2, 4);

    Room target(Room::RoomType::EMPTY, player);
    target = std::move(original); // Присваиваем перемещением

    // Проверяем что данные переместились
    EXPECT_EQ(target.getCoordinates().first, 2);
    EXPECT_EQ(target.getCoordinates().second, 4);
    EXPECT_EQ(target.getType(), Room::RoomType::EVENT);
}