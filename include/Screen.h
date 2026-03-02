// Screen.h
#ifndef SCREEN_H
#define SCREEN_H

#include <iostream>
#include <string>
#include <vector>
#include "Dungeon.h"
#include "Player.h"

/**
 * @brief Класс для отрисовки игры в консоли
 * Упрощенная версия - только ASCII символы для комнат
 */
class Screen {
public:
    // Символы для отрисовки комнат - constexpr
    static constexpr char EXIT_ROOM = 'E';
    static constexpr char VISITED_ROOM = '◙';
    static constexpr char UNKNOWN_ROOM = '?';
    static constexpr char PLAYER_SYMBOL = '@';

    /**
     * @brief Очистка экрана
     */
    static void clearScreen(); //очищает консоль

    /**
     * @brief Отрисовка карты подземелья
     */
    static void drawDungeonMap(const Dungeon& dungeon, const Player& player);

    /**
     * @brief Отрисовка информации о текущей комнате
     */
    static void drawCurrentRoomInfo(const Dungeon& dungeon);

    /**
     * @brief Отрисовка инвентаря
     */
    static void drawPlayerInventory(const Player& player);

    /**
     * @brief Отрисовка сообщения
     */
    static void drawMessage(const std::string& message);

    /**
     * @brief Отрисовка меню
     */
    static void drawMenu(const std::vector<std::string>& options, int selected = 0);

    /**
     * @brief Отрисовка боя
     */
    static void drawBattle(const Player& player, const Monster& monster);

private:
    /**
     * @brief Получение символа комнаты по её типу
     */
    static char getRoomSymbol(const Room& room, bool isCurrent, bool isVisited);
};

#endif // SCREEN_H