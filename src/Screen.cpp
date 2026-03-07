#include "../include/Screen.h"


    // Символы для отрисовки комнат - constexpr
    // static constexpr char EXIT_ROOM = 'E';
    // static constexpr char VISITED_ROOM = '◙';
    // static constexpr char UNKNOWN_ROOM = '?';
    // static constexpr char PLAYER_SYMBOL = '@';

    void Screen::clearScreen() {
        std::cout << "\033[2J\033[1;1H";  //очищает консоль
    }
    static void drawDungeonMap(const Dungeon& dungeon, const Player& player){} //Отрисовка карты подземелья
    static void drawCurrentRoomInfo(const Dungeon& dungeon); //Отрисовка информации о текущей комнате

     void Screen::drawInventory(const Player& player) {
        char EMPTY_SLOT = 'X';
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
        for (int i = 0; i < 8; i++) {
            if (i < player.getInventorySize()) {
                // Получаем предмет из инвентаря
                auto item = player.getItem(i);
                if (item) {
                    char sym = EMPTY_SLOT;
                    if (item->getItemType() == "weapon") sym = WEAPON_SYM;
                    else if (item->getItemType() == "potion") sym = POTION_SYM;
                    else if (item->getItemType() == "armor") sym = ARMOR_SYM;

                    std::cout << "  " << sym << "  │";
                }
            } else {
                std::cout << "  " << EMPTY_SLOT << "  │";
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


        // Если есть предметы - показываем их описания
        if (player.getInventorySize() > 0) {
            std::cout << "Предметы:\n";
            for (int i = 0; i < player.getInventorySize(); i++) {
                auto item = player.getItem(i);
                if (item) {
                    std::cout << "  " << (i+1) << ". " << item->getName()
                             <<"\n";
                }
            }
        } else {
            std::cout << "Инвентарь пуст. Найдите предметы в подземелье!\n";
        }

        std::cout << "\n──────────────────────────────────────────────────\n";
        std::cout << "Использовать: u [номер]  |  Назад: b\n";
    };


    /**
     * @brief Отрисовка сообщения
     */
void Screen::drawMessage(const std::string& message) {
    std::cout << "\n";
    std::cout << "╔══════════════════════════════════════════════════════════╗\n";
    std::cout << "║                       СООБЩЕНИЕ                          ║\n";
    std::cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    // Разбиваем длинное сообщение на строки по 50 символов
    std::string msg = message;
    size_t maxLength = 100;

    while (msg.length() > maxLength) {
        size_t spacePos = msg.find_last_of(' ', maxLength);
        if (spacePos == std::string::npos) spacePos = maxLength;

        std::cout << "  " << msg.substr(0, spacePos) << "\n";
        msg = msg.substr(spacePos + 1);
    }
    if (!msg.empty()) {
        std::cout << "  " << msg << "\n";
    }

    std::cout << "\n──────────────────────────────────────────────────\n";
    std::cout << "  Нажмите Enter чтобы продолжить...";
    std::cin.get();
}

    /**
     * @brief Отрисовка меню
     */
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
int Screen::chooseAction() {
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

    int choice;
    std::cin >> choice;
    return choice;
}

    /**
     * @brief Отрисовка боя
     */
    static void drawBattle(const Player& player, const Monster& monster);
    /**
     * @brief Получение символа комнаты по её типу
     */
    static char getRoomSymbol(const Room& room, bool isCurrent, bool isVisited);