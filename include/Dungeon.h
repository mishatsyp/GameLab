#ifndef DUNGEON_H
#define DUNGEON_H

#include <vector>
#include <memory>
#include <optional>
#include "Room.h"
#include "Random.h"

/**
 * @brief Класс подземелья (уровня)
 * Управляет комнатами и генерацией уровня
 */
class Dungeon {
private:
    // Вектор комнат - можно использовать как линейный уровень или сетку
    std::vector<std::unique_ptr<Room>> rooms;

    int currentRoomIndex;
    int levelNumber;

    // Параметры генерации - constexpr для оптимизации
    static constexpr int MIN_ROOMS = 5;
    static constexpr int MAX_ROOMS = 10;
    static constexpr int MIN_ROOM_SIZE = 6;
    static constexpr int MAX_ROOM_SIZE = 12;

public:
    // Конструктор генерирует подземелье
    explicit Dungeon(int level = 1);

    // Запрещаем копирование
    Dungeon(const Dungeon&) = delete;
    Dungeon& operator=(const Dungeon&) = delete;

    // Разрешаем перемещение
    Dungeon(Dungeon&&) noexcept = default;
    Dungeon& operator=(Dungeon&&) noexcept = default;

    /**
     * @brief Генерация нового уровня
     * @param level номер уровня (влияет на сложность)
     */
    void generateLevel(int level);

    /**
     * @brief Переход в следующую комнату
     * @return std::optional<Room*> - указатель на комнату или nullopt
     */
    std::optional<Room*> goToNextRoom();

    /**
     * @brief Получение текущей комнаты
     * @return Room* или nullptr (можно обернуть в optional)
     */
    Room* getCurrentRoom() const;

    /**
     * @brief Получение комнаты по индексу
     * @param index индекс комнаты
     * @return std::optional<Room*> - комната или nullopt
     */
    std::optional<Room*> getRoom(int index);

    /**
     * @brief Количество комнат на уровне
     */
    size_t getRoomCount() const { return rooms.size(); }

    /**
     * @brief Номер текущего уровня
     */
    int getLevelNumber() const { return levelNumber; }

    /**
     * @brief Проверка, пройден ли уровень
     */
    bool isLevelComplete() const;

    /**
     * @brief Создание следующего уровня
     * @return unique_ptr на новый Dungeon
     */
    std::unique_ptr<Dungeon> createNextLevel();

private:
    /**
     * @brief Генерация случайной комнаты
     * @return unique_ptr на сгенерированную комнату
     */
    std::unique_ptr<Room> generateRandomRoom();
};

#endif // DUNGEON_H