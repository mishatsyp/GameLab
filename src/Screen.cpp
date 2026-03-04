#include "../include/Screen.h"


    // Символы для отрисовки комнат - constexpr
    // static constexpr char EXIT_ROOM = 'E';
    // static constexpr char VISITED_ROOM = '◙';
    // static constexpr char UNKNOWN_ROOM = '?';
    // static constexpr char PLAYER_SYMBOL = '@';

    static void Screen::clearScreen() {
        std::cout << "\033[2J\033[1;1H";  //очищает консоль
    }
    static void drawDungeonMap(const Dungeon& dungeon, const Player& player){} //Отрисовка карты подземелья
    static void drawCurrentRoomInfo(const Dungeon& dungeon); //Отрисовка информации о текущей комнате
    static void drawPlayerInventory(const Player& player) {} //Отрисовка инвентаря

    static void Screen::drawInventory(const Player& player) {
        constexpr char EMPTY_SLOT = '·';
        constexpr char WEAPON_SYM = '⚔';  // меч
        constexpr char POTION_SYM = '🧪'; // зелье (можно заменить на '▲' если не поддерживается)
        constexpr char ARMOR_SYM = '🛡';   // броня (можно заменить на '◆' если не поддерживается)
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
    static void drawMessage(const std::string& message);

    /**
     * @brief Отрисовка меню
     */
    static void drawMenu(const std::vector<std::string>& options, int selected = 0);

    /**
     * @brief Отрисовка боя
     */
    static void drawBattle(const Player& player, const Monster& monster);
    /**
     * @brief Получение символа комнаты по её типу
     */
    static char getRoomSymbol(const Room& room, bool isCurrent, bool isVisited);