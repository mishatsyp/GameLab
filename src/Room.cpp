#include "../include/Room.h"
#include "../include/Player.h"
#include "../include/Event.h"
#include <memory>
#include <string>

// Конструктор
Room::Room(RoomType roomType)
    : type(roomType)
    , isExplored(false) {

    // Если комната с событием, создаем событие
    if (type == RoomType::EVENT) {
        roomEvent = std::make_unique<Event>();
    }
}

// Генерация контента (пока ничего не делает)
void Room::generateRoomContent() {

}

// Вход в комнату
std::string Room::enter(Player& player) {
    if (!isExplored) {
        isExplored = true;

        if (type == RoomType::EMPTY) {
            return "Вы вошли в пустую комнату.";
        }
        else if (type == RoomType::EVENT) {
            return "Вы вошли в комнату с событием!";
        }
        else if (type == RoomType::EXIT) {
            return "Вы нашли выход!";
        }
    }

    return "Вы снова в этой комнате.";
}

// Осмотр комнаты
std::string Room::look() const {
    if (type == RoomType::EMPTY) {
        return "Пустая комната.";
    }
    else if (type == RoomType::EVENT) {
        if (roomEvent) {
            return roomEvent->getDescription();
        }
        return "Здесь что-то происходит...";
    }
    else {
        return "Здесь выход!";
    }
}

// Проверка активного события
bool Room::hasActiveEvent() const {
    if (roomEvent) {
        return !roomEvent->getIsCompleted();
    }
    return false;
}