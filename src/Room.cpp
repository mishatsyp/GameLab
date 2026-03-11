// Room.cpp
#include "../include/Room.h"
#include "../include/Random.h"
#include "../include/Screen.h"
#include "../include/Event.h"
#include <iostream>

Room::Room(RoomType roomType, Player& p) : type(roomType), isExplored(false) {
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

void Room::look() const {
    std::string result;
    // if (isCompleted != true) {
    //     player.setCheckedRooms(player.getCheckedRooms()+1); // !!!!!!!!!!!!!!!!!!!!!!!!!
    // }

    // В зависимости от типа комнаты
    switch(type) {
        case RoomType::EMPTY:
            if (isExplored) {
                Screen::drawMessage("Вы снова в пустой комнате. Ничего не изменилось.");
            } else {
                Screen::drawMessage("Пустая комната. Здесь ничего нет.");
            }
            break;

        case RoomType::EVENT:
            if (isExplored) {
                if (roomEvent && !roomEvent->getIsCompleted()) {
                    Screen::drawMessage("Событие все еще активно.");
                } else {
                    Screen::drawMessage("Вы уже прошли это событие. В комнате ничего не изменилось.");
                }
            } else {
                if (roomEvent) {
                    Screen::drawMessage(roomEvent->getDescription());
                    // Screen::drawMessage(roomEvent->getOutcomes());
                    for (auto& x : roomEvent->getOutcomes()) {
                        Screen::drawMessage(x);
                    }
                } else {
                    Screen::drawMessage("Странная комната...");
                }
            }
            break;

        case RoomType::MONSTER:
            if (isExplored) {
                Screen::drawMessage("Вы снова в комнате с монстром.");
            } else {
                Screen::drawMessage("В комнате монстр! Приготовьтесь к бою!");
            }
            break;

        case RoomType::EXIT:
            Screen::drawMessage("Вы нашли выход на следующий уровень!");
            break;
    }
}