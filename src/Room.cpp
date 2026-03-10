// Room.cpp
#include "../include/Room.h"
#include "../include/Random.h"
#include "../include/Screen.h"
#include <iostream>

Room::Room(RoomType roomType, Player p) : type(roomType), isExplored(false) {
    generateRoomContent(p);
}

void Room::generateRoomContent(Player& p) {
    Random& rng = Random::getInstance();

    // Если комната с монстром - ничего не генерируем (будет бой)
    if (type == RoomType::MONSTER) {
        return;
    }

    // Если тип не задан (EMPTY), рандомно выбираем между EMPTY и EVENT
    if (type == RoomType::EMPTY) {
        // 70% шанс на ивент, 30% на пустую
        int chance = rng.getInt(1, 100);
        if (chance <= 70) {
            type = RoomType::EVENT;
        }
    }

    // Если комната с ивентом - создаем событие
    if (type == RoomType::EVENT) {
        roomEvent = std::make_unique<Event>();
        roomEvent->generateRandomEvent(1, p); // уровень 1 по умолчанию
    }
}

std::string Room::look() const {
    std::string result;

    // В зависимости от типа комнаты
    switch(type) {
        case RoomType::EMPTY:
            if (isExplored) {
                result = "Вы снова в пустой комнате. Ничего не изменилось.";
            } else {
                result = "Пустая комната. Здесь ничего нет.";
            }
            break;

        case RoomType::EVENT:
            if (isExplored) {
                if (roomEvent && !roomEvent->getIsCompleted()) {
                    result = "Событие все еще активно.";
                } else {
                    result = "Вы уже прошли это событие. В комнате ничего не изменилось.";
                }
            } else {
                if (roomEvent) {
                    result = roomEvent->getDescription();
                } else {
                    result = "Странная комната...";
                }
            }
            break;

        case RoomType::MONSTER:
            if (isExplored) {
                result = "Вы снова в комнате с монстром.";
            } else {
                result = "В комнате монстр! Приготовьтесь к бою!";
            }
            break;
    }

    return result;
}