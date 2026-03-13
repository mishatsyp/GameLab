#include "../include/Screen.h"
#include "../include/Item.h"
#include "../include/Player.h"
#include "../include/Dungeon.h"
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
    std::cout << "⚔️ ЭКИПИРОВАНО:\n";
    std::cout << "──────────────────────────────────────────────────\n";
    auto weapon = player.getEquippedWeapon();
    if (weapon) {
        std::cout << "⚔ Оружие: " << weapon->getName()
                  << " (урон +" << weapon->getDamage()
                  << ", прочность " << weapon->getItemDurability() << ")\n";
    } else {std::cout << "⚔ Оружие: пусто\n";}

    auto armor = player.getEquippedArmor();
    if (armor) {
        std::cout << "🛡 Броня:  " << armor->getName()
                  << " (защита +" << armor->getDefense()
                  << ", прочность " << armor->getItemDurability() << ")\n";
    } else {std::cout << "🛡 Броня:  пусто\n";}

    std::cout << "\n";
    std::cout << "📦 ИНВЕНТАРЬ:\n";
    std::cout << "──────────────────────────────────────────────────\n";
    std::cout << "┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐\n";
    std::cout << "│";
    for (int i = 0; i < 8; i++) {
        if (i < player.getInventorySize()) {
            auto itemOpt = player.getItem(i);
            if (itemOpt.has_value()) {
                const auto& item = itemOpt.value();
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
    std::cout << "├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤\n";
    std::cout << "│";
    for (int i = 0; i < 8; i++) {
        std::cout << "  " << (i+1) << "  │";
    }
    std::cout << "\n";
    std::cout << "└─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘\n\n";

    if (player.getInventorySize() > 0) {
        for (int i = 0; i < player.getInventorySize(); i++) {
            auto itemOpt = player.getItem(i);
            if (itemOpt.has_value()) {
                const auto& item = itemOpt.value();
                std::cout << "  " << (i+1) << ". " << item->getName();

                if (item->getItemType() == "Weapon") {
                    if (const auto weaponPtr = std::dynamic_pointer_cast<Weapon>(item)) {
                        std::cout << " (урон +" << weaponPtr->getDamage()
                                  << ", пр. " << weaponPtr->getItemDurability() << ")";
                    }
                } else if (item->getItemType() == "Armor") {
                    if (const auto armorPtr = std::dynamic_pointer_cast<Armor>(item)) {
                        std::cout << " (защита +" << armorPtr->getDefense()
                                  << ", пр. " << armorPtr->getItemDurability() << ")";
                    }
                } else if (item->getItemType() == "Potion") {
                    if (const auto potionPtr = std::dynamic_pointer_cast<Potion>(item)) {
                        std::cout << " (лечит " << potionPtr->getHealAmount() << " HP)";
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

void Screen::drawDungeonMap(const Dungeon& dungeon) {
    std::cout << "\n";
    std::cout << "╔══════════════════════════════════════════════════════════╗\n";
    std::cout << "║                      КАРТА ПОДЗЕМЕЛЬЯ                    ║\n";
    std::cout << "╚══════════════════════════════════════════════════════════╝\n\n";
    int height = 4;
    int width = 4;
    for (int y = 0; y < height; y++) {
        std::cout << "  ";
        for (int x = 0; x < width; x++) {
            int cell = dungeon.getCell(x, y);
            bool isPlayerHere = (x == dungeon.getCurrentX() && y == dungeon.getCurrentY());

            if (cell == 0) {
                std::cout << "██████";
            } else if (cell == 1) {
                if (isPlayerHere) {
                    std::cout << "[ 👤 ]";
                } else {
                    std::cout << "[ ☐ ]";
                }
            } else if (cell == 2) {
                if (isPlayerHere) {
                    std::cout << "[ 👤➡]";
                } else {
                    std::cout << "[ ➡ ]";
                }
            }
        }
        std::cout << "\n";
    }
    std::cout << "──────────────────────────────────────────────────\n";
    std::cout << "  ☐ - комната    ➡ - выход    👤 - вы здесь\n";
    std::cout << "──────────────────────────────────────────────────\n";
}

