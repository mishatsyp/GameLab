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
        EMPTY,
        EVENT,
        // MONSTER,
        EXIT
    };
private:
    std::pair<int,int> coordinates;
    RoomType type;
    bool isExplored;
    std::unique_ptr<Event> roomEvent;
public:
    Room(RoomType roomType, Player& player);
    Room(const Room&) = delete;
    Room& operator=(const Room&) = delete;
    Room(Room&&) noexcept = default;
    Room& operator=(Room&&) noexcept = default;
    void generateRoomContent(Player& player);
    void look(Player& player);
    RoomType getType() const { return type; }
    bool getisExplored() const {return isExplored;}
    std::pair<int,int> getCoordinates() const {return coordinates;}
    void setCoordinates(int x, int y) { coordinates = {x, y}; }
    std::optional<Event*> GetEvent() const;
};

#endif // ROOM_H