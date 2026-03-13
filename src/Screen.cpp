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
    char WEAPON_SYM = 'W';  // меч
    char ARMOR_SYM = 'A';   // броня
    char POTION_SYM = 'P';  // зелье

    std::cout << "\n";
    std::cout << "╔══════════════════════════════════════════════════════════╗\n";
    std::cout << "║                        ИНВЕНТАРЬ                        ║\n";
    std::cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    // ЭКИПИРОВКА (вверху)
    std::cout << "⚔️ ЭКИПИРОВАНО:\n";
    std::cout << "──────────────────────────────────────────────────\n";

    // Оружие
    auto weapon = player.getEquippedWeapon();
    if (weapon) {
        std::cout << "⚔ Оружие: " << weapon->getName()
                  << " (урон +" << weapon->getDamage()
                  << ", прочность " << weapon->getItemDurability() << ")\n";
    } else {
        std::cout << "⚔ Оружие: пусто\n";
    }

    // Броня
    auto armor = player.getEquippedArmor();
    if (armor) {
        std::cout << "🛡 Броня:  " << armor->getName()
                  << " (защита +" << armor->getDefense()
                  << ", прочность " << armor->getItemDurability() << ")\n";
    } else {
        std::cout << "🛡 Броня:  пусто\n";
    }

    std::cout << "\n";

    // ИНВЕНТАРЬ
    std::cout << "📦 ИНВЕНТАРЬ:\n";
    std::cout << "──────────────────────────────────────────────────\n";

    // Верхняя рамка
    std::cout << "┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐\n";

    // Строка с иконками
    std::cout << "│";
    for (int i = 0; i < 8; i++) {
        if (i < player.getInventorySize()) {
            auto itemOpt = player.getItem(i);
            if (itemOpt.has_value()) {
                auto item = itemOpt.value();
                char sym = EMPTY_SLOT;
                if (item->getItemType() == "Weapon") sym = WEAPON_SYM;
                else if (item->getItemType() == "Armor") sym = ARMOR_SYM;
                else if (item->getItemType() == "Potion") sym = POTION_SYM;
                std::cout << "  " << sym << "  │";
            } else {
                std::cout << "  " << EMPTY_SLOT << "  │";
            }
        } else {
            std::cout << "  " << EMPTY_SLOT << "  │";
        }
    }
    std::cout << "\n";

    // Номера слотов
    std::cout << "├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤\n";
    std::cout << "│";
    for (int i = 0; i < 8; i++) {
        std::cout << "  " << (i+1) << "  │";
    }
    std::cout << "\n";
    std::cout << "└─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘\n\n";

    // Список предметов в инвентаре
    if (player.getInventorySize() > 0) {
        for (int i = 0; i < player.getInventorySize(); i++) {
            auto itemOpt = player.getItem(i);
            if (itemOpt.has_value()) {
                auto item = itemOpt.value();
                std::cout << "  " << (i+1) << ". " << item->getName();

                if (item->getItemType() == "Weapon") {
                    auto weapon = std::dynamic_pointer_cast<Weapon>(item);
                    if (weapon) {
                        std::cout << " (урон +" << weapon->getDamage()
                                  << ", пр. " << weapon->getItemDurability() << ")";
                    }
                } else if (item->getItemType() == "Armor") {
                    auto armor = std::dynamic_pointer_cast<Armor>(item);
                    if (armor) {
                        std::cout << " (защита +" << armor->getDefense()
                                  << ", пр. " << armor->getItemDurability() << ")";
                    }
                } else if (item->getItemType() == "Potion") {
                    auto potion = std::dynamic_pointer_cast<Potion>(item);
                    if (potion) {
                        std::cout << " (лечит " << potion->getHealAmount() << " HP)";
                    }
                }
                std::cout << "\n";
            }
        }
    } else {
        std::cout << "  Инвентарь пуст\n";
    }
}

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
    std::cout << "             ░   Leonid Vorobiev       ░\n";
    std::cout << "             ░   Syuzi Tumanian        ░\n";
    std::cout << "             ░   Lubov Istomina        ░\n";
    std::cout << "             ░   Michael Tsypchenko    ░\n";
    std::cout << "             ░░░░░░░░░░░░░░░░░░░░░░░░░░░\n\n";

    std::cout << "──────────────────────────────────────────────────\n";
    std::cout << "         Спасибо за игру! Press Enter to exit\n";
    //std::cin.get();
}

void Screen::drawMenu() {
        clearScreen();
        std::cout << "\n";
        std::cout << "╔══════════════════════════════════════════════════════════╗\n";
        std::cout << "║                   DUNGEON CRAWLER                        ║\n";
        std::cout << "╚══════════════════════════════════════════════════════════╝\n\n";
        std::cout << "                 ░░░░░░░░░░░░░░░░░░░░░░░░░░░\n";
        std::cout << "                 ░      DUNGEON CRAWLER    ░\n";
        std::cout << "                 ░░░░░░░░░░░░░░░░░░░░░░░░░░░\n\n";
        std::cout << "                    ╔════════════════╗\n";
        std::cout << "                    ║  1. НОВАЯ ИГРА ║\n";
        std::cout << "                    ║  2. ВЫХОД      ║\n";
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
    std::cout << "║                      КАРТА ПОДЗЕМЕЛЬЯ                    ║\n";
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

