// Screen.h
    #ifndef SCREEN_H
#define SCREEN_H

#include <iostream>
#include <string>
#include <vector>
#include "GameEngine.h"
#include "Player.h"

class Screen {
public:
    // Символы для отрисовки комнат - constexpr
    static constexpr char EXIT_ROOM = 'E';
    static constexpr char VISITED_ROOM = 'X';
    static constexpr char UNKNOWN_ROOM = '?';
    static constexpr char PLAYER_SYMBOL = '@';

    /**
     * @brief Очистка экрана
     */
    static void clearScreen();

    /**
     * @brief Отрисовка карты подземелья
     */
    static void drawDungeonMap(const Dungeon& dungeon);

    /**
     * @brief Отрисовка информации о текущей комнате
     */
    static void drawCurrentRoomInfo(const Dungeon& dungeon);

    /**
     * @brief Отрисовка инвентаря
     */
    static void drawInventory(const Player& player);

    /**
     * @brief Отрисовка сообщения
     */
    static void drawMessage(const std::string& message);

    /**
     * @brief Отрисовка меню
     */
    static void drawMenu();

    /**
     * @brief Отрисовка боя
     */
    static void drawBattle(const Player& player, const Monster& monster);

    static int chooseAction();

private:
    /**
     * @brief Получение символа комнаты по её типу
     */
    static char getRoomSymbol(const Room& room, bool isCurrent, bool isVisited);
};

#endif // SCREEN_H