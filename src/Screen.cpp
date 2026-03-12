#include "../include/Screen.h"
#include "../include/Item.h"
#include "../include/Player.h"
#include "../include/Dungeon.h"


    // Символы для отрисовки комнат - constexpr
    // static constexpr char EXIT_ROOM = 'E';
    // static constexpr char VISITED_ROOM = '◙';
    // static constexpr char UNKNOWN_ROOM = '?';
    // static constexpr char PLAYER_SYMBOL = '@';

    void Screen::clearScreen() {}
     void Screen::drawInventory(const Player& player) {
        char EMPTY_SLOT = ' ';
        char WEAPON_SYM = 'S';  // меч
        char POTION_SYM = 'P'; // зелье (можно заменить на '▲' если не поддерживается)
        char ARMOR_SYM = 'A';   // броня (можно заменить на '◆' если не поддерживается)
        std::cout << "\n";
        std::cout << "╔══════════════════════════════════════════════════════════╗\n";
        std::cout << "║                        ИНВЕНТАРЬ                        ║\n";
        std::cout << "╚══════════════════════════════════════════════════════════╝\n\n";

        // Верхняя рамка инвентаря
        std::cout << "┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐\n";

        // Строка с иконками предметов
        std::cout << "│";
        if (player.getInventorySize() > 0) {
            std::cout << "Предметы:\n";
            for (int i = 0; i < player.getInventorySize(); i++) {
                auto itemOpt = player.getItem(i);
                if (itemOpt.has_value()) {
                    Item* item = itemOpt.value();
                    std::cout << "  " << (i+1) << ". " << item->getName() << "\n";
                }
            }
        }
        std::cout << "\n";

        // Средняя рамка (разделитель)
        std::cout << "├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤\n";

        // Строка с номерами слотов
        std::cout << "│";
        for (int i = 0; i < 8; i++) {
            std::cout << "  " << (i+1) << "  │";
        }
        std::cout << "\n";

        // Нижняя рамка
        std::cout << "└─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘\n\n";

        // Легенда
        std::cout << "Легенда: " << WEAPON_SYM << " - оружие  "
                  << POTION_SYM << " - зелье  "
                  << ARMOR_SYM << " - броня\n\n";


        if (player.getInventorySize() > 0) {
            std::cout << "Предметы:\n";
            for (int i = 0; i < player.getInventorySize(); i++) {
                auto itemOpt = player.getItem(i);
                if (itemOpt.has_value()) {
                    Item* item = itemOpt.value();
                    std::cout << "  " << (i+1) << ". " << item->getName() << "\n";
                }
            }
        }else {
            std::cout << "Инвентарь пуст. Найдите предметы в подземелье!\n";
        }
        std::cout << "\n──────────────────────────────────────────────────\n";
    };


    /**
     * @brief Отрисовка сообщения
     */
void Screen::drawMessage(const std::string& message) {
    std::cout << "\n";
    // Разбиваем длинное сообщение на строки по 50 символов
    std::string msg = message;
    size_t maxLength = 1000;

    while (msg.length() > maxLength) {
        size_t spacePos = msg.find_last_of(' ', maxLength);
        if (spacePos == std::string::npos) spacePos = maxLength;

        std::cout << "  " << msg.substr(0, spacePos) << "\n";
        msg = msg.substr(spacePos + 1);
    }
    if (!msg.empty()) {
        std::cout << "  " << msg << "\n";
    }
}

// Screen.h - добавить
static void drawGameOver();

// Screen.cpp
void Screen::drawGameOver() {
    clearScreen();

    std::cout << "\n";
    std::cout << "╔══════════════════════════════════════════════════════════╗\n";
    std::cout << "║                     GAME OVER                            ║\n";
    std::cout << "╚══════════════════════════════════════════════════════════╝\n\n";
    std::cout << "──────────────────────────────────────────────────\n";
    std::cout << "              РАЗРАБОТЧИКИ ПРОЕКТА\n";
    std::cout << "──────────────────────────────────────────────────\n\n";

    std::cout << "             ░░░░░░░░░░░░░░░░░░░░░░░░░░░\n";
    std::cout << "             ░   Leonid Vorobiev     ░\n";
    std::cout << "             ░   Suzi Tymanian       ░\n";
    std::cout << "             ░   Lubov Istomina      ░\n";
    std::cout << "             ░   Michael Tsypchenko  ░\n";
    std::cout << "             ░░░░░░░░░░░░░░░░░░░░░░░░░░░\n\n";

    std::cout << "──────────────────────────────────────────────────\n";
    std::cout << "         Спасибо за игру! Press Enter to exit\n";
    std::cin.get();
}

void Screen::drawMenu() {
        clearScreen();
        std::cout << "\n";
        std::cout << "╔══════════════════════════════════════════════════════════╗\n";
        std::cout << "║                   DUNGEON CRAWLER                        ║\n";
        std::cout << "╚══════════════════════════════════════════════════════════╝\n\n";
        std::cout << "                 ░░░░░░░░░░░░░░░░░░░░░░░░░░░\n";
        std::cout << "                 ░      DUNGEON CRAWLER   ░\n";
        std::cout << "                 ░░░░░░░░░░░░░░░░░░░░░░░░░░░\n\n";
        std::cout << "                    ╔════════════════╗\n";
        std::cout << "                    ║  1. НОВАЯ ИГРА  ║\n";
        std::cout << "                    ║  2. ВЫХОД       ║\n";
        std::cout << "                    ╚════════════════╝\n\n";
        std::cout << "──────────────────────────────────────────────────\n";
        std::cout << "  Введите 1 или 2: ";
    }

// Screen.h
static int showActionMenu();

// Screen.cpp
void Screen::chooseAction() {
    std::cout << "\n";
    std::cout << "╔══════════════════════════════════════════════════════════╗\n";
    std::cout << "║                      ВЫБЕРИТЕ ДЕЙСТВИЕ                   ║\n";
    std::cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    std::cout << "                    ╔════════════════════╗\n";
    std::cout << "                    ║  1. Осмотреть      ║\n";
    std::cout << "                    ║     комнату        ║\n";
    std::cout << "                    ╠════════════════════╣\n";
    std::cout << "                    ║  2. Открыть        ║\n";
    std::cout << "                    ║     инвентарь      ║\n";
    std::cout << "                    ╠════════════════════╣\n";
    std::cout << "                    ║  3. Пройти в       ║\n";
    std::cout << "                    ║     следующую      ║\n";
    std::cout << "                    ╚════════════════════╝\n\n";

    std::cout << "──────────────────────────────────────────────────\n";
    std::cout << "  Введите номер действия (1-3): ";
}

    /**
     * @brief Отрисовка боя
     */
    static void drawBattle(const Player& player, const Monster& monster);
    /**
     * @brief Получение символа комнаты по её типу
     */
    static char getRoomSymbol(const Room& room, bool isCurrent, bool isVisited);

// Screen.h добавить
static void drawDungeonMap(const Dungeon& dungeon);

// Screen.cpp
void Screen::drawDungeonMap(const Dungeon& dungeon) {
    std::cout << "\n";
    std::cout << "╔══════════════════════════════════════════════════════════╗\n";
    std::cout << "║                      КАРТА ПОДЗЕМЕЛЬЯ                   ║\n";
    std::cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    // Получаем размеры матрицы
    int height = 4;  // в наших паттернах всегда 4 строки
    int width = 4;   // в наших паттернах всегда 4 столбца

    // Рисуем карту
    for (int y = 0; y < height; y++) {
        std::cout << "  ";
        for (int x = 0; x < width; x++) {
            int cell = dungeon.getCell(x, y);

            // Проверяем, находится ли игрок в этой клетке
            bool isPlayerHere = (x == dungeon.getCurrentX() && y == dungeon.getCurrentY());

            if (cell == 0) {
                // Пустота (стена)
                std::cout << "██████";
            } else if (cell == 1) {
                // Обычная комната
                if (isPlayerHere) {
                    std::cout << "[ 👤 ]";  // игрок в комнате
                } else {
                    std::cout << "[ ☐ ]";  // пустая комната
                }
            } else if (cell == 2) {
                // Выход
                if (isPlayerHere) {
                    std::cout << "[ 👤➡]";  // игрок на выходе
                } else {
                    std::cout << "[ ➡ ]";  // выход
                }
            }
        }
        std::cout << "\n";  // двойной отступ между рядами
    }

    // Легенда
    std::cout << "──────────────────────────────────────────────────\n";
    std::cout << "  ☐ - комната    ➡ - выход    👤 - вы здесь\n";
    std::cout << "──────────────────────────────────────────────────\n";
}

