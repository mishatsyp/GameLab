#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <memory>
#include <optional>
#include "Entity.h"
#include "Item.h"
#include "Screen.h"

class Player {
private:
    std::string name;
    bool inBattle;  // Флаг, находимся ли мы в бою
    // Инвентарь - unique_ptr для предметов
    std::vector<std::unique_ptr<Item>> inventory;
    int health;
    int damage;
    int level;
    static constexpr size_t MAX_INVENTORY_SIZE = 8;
    std::pair<int, int> position;
public:
    explicit Player(const std::string& playerName);
    // virtual ~Player() override = default; <- incorrect
    ~Player() = default;

    // Реализация виртуальных методов
    void attack(Entity& target); // deleted virtual, override
    // Методы игрока
    bool addItem(std::unique_ptr<Item> item);
    bool useItem(size_t itemIndex);
    int getHealth() const;
    void setHealth(int h);
    int getDamage() const;
    void setDamage(int d);
    void showInventory() const;
    int getInventorySize() const;
    Item* getItem(size_t itemIndex) const;
    int getLevel() const;
    void setLevel(int l);
};

#endif // PLAYER_H