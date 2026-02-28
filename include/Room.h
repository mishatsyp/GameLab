// Room.h
#ifndef ROOM_H
#define ROOM_H

#include <memory>
#include <optional>
#include <string>
#include "Event.h"

class Room {
private:
    RoomType type;
    bool isExplored;           // Были ли уже в этой комнате

    // Событие в комнате (если тип EVENT)
    std::unique_ptr<Event> roomEvent;

public:
    enum class RoomType {
        EMPTY,      // Пустая комната (только осмотреться)
        EVENT,      // Комната с событием
        EXIT        // Выход на следующий уровень
    };
    /**
     * @param roomType тип комнаты
     * @param number номер комнаты
     */
    Room(RoomType roomType);

    // Запрещаем копирование (из-за unique_ptr)
    Room(const Room&) = delete;
    Room& operator=(const Room&) = delete;

    // Разрешаем перемещение
    Room(Room&&) noexcept = default;
    Room& operator=(Room&&) noexcept = default;

    // /**
    //  * @brief Генерация названия и описания комнаты
    //  */
    // void generateRoomContent();

    // /**
    //  * @brief Вход в комнату
    //  * @param player ссылка на игрока
    //  * @return текст, описывающий что произошло
    //  */
    // std::string enter(Player& player);
    //
    /**
     * @brief Осмотреться в комнате
     * @return описание того, что можно увидеть
     */
    std::string look() const;

    // Геттеры
    RoomType getType() const { return type; }
    bool isExplored() const { return isExplored; }
    /**
     * @brief Проверка, есть ли в комнате непройденное событие
     */
    // bool hasActiveEvent() const {
    //     return roomEvent && !roomEvent->isCompleted();
    // }
    //
    /**
     * @brief Получить событие комнаты
     */
    Event* getEvent() const { return roomEvent.get(); }
};

#endif // ROOM_H