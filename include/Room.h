 // Room.h
#ifndef ROOM_H
#define ROOM_H

#pragma once
#include <memory>
#include <optional>
#include <string>

class Event;
class Player;

class Room {
public:
    enum class RoomType {
        EMPTY,      // Пустая комната (только осмотреться)
        EVENT,      // Комната с событием
        MONSTER     // Выход на следующий уровень
    };
private:
    std::pair<int,int> coordinates;
    RoomType type;
    bool isExplored;           // Были ли уже в этой комнате
    std::unique_ptr<Event> roomEvent; // Событие в комнате (если тип EVENT)
public:
    Room(RoomType roomType, Player& player); // Запрещаем копирование (из-за unique_ptr)
    Room(const Room&) = delete;
    Room& operator=(const Room&) = delete;
    Room(Room&&) noexcept = default; // Разрешаем перемещение
    Room& operator=(Room&&) noexcept = default;
    void generateRoomContent(Player& player);
    void look() const;
    RoomType getType() const { return type; }
    bool getisExplored() const {return isExplored;}
    //Event* getEvent() const { return roomEvent.get(); }
    std::pair<int,int> getCoordinates() const {return coordinates;}
    void setCoordinates(int x, int y) { coordinates = {x, y}; }
    Event* GetEvent() const { return roomEvent.get();}
};

#endif // ROOM_H