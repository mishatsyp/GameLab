 // Room.h
#ifndef ROOM_H
#define ROOM_H

#include <memory>
#include <optional>
#include <string>
#include "Event.h"

class Room {
private:
    enum class RoomType {
        EMPTY,      // Пустая комната (только осмотреться)
        EVENT,      // Комната с событием
        MONSTER     // Выход на следующий уровень
    };
    std::pair<int,int> coordinates;
    RoomType type;
    bool isExplored;           // Были ли уже в этой комнате
    std::unique_ptr<Event> roomEvent; // Событие в комнате (если тип EVENT)
public:
    Room(RoomType roomType); // Запрещаем копирование (из-за unique_ptr)
    Room(const Room&) = delete;
    Room& operator=(const Room&) = delete;
    Room(Room&&) noexcept = default; // Разрешаем перемещение
    Room& operator=(Room&&) noexcept = default;
    void generateRoomContent();
    std::string look() const;
    RoomType getType() const { return type; }
    bool getisExplored() const {return isExplored;}
    //Event* getEvent() const { return roomEvent.get(); }
};

#endif // ROOM_H