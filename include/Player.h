#ifndef PLAYER_H
#define PLAYER_H

#pragma once
#include <string>
#include <vector>
#include <memory>
#include <optional>
#include "Entity.h"
//#include "Item.h"
// #include "Screen.h"

class Armor;
class Item;
class Weapon;

class Player {
private:
    std::string name;
    bool inBattle;
    int health;
    int damage;
    int level;
    int checked_rooms;
    bool isDefending;
    std::unique_ptr<Weapon> equippedWeapon;
    std::unique_ptr<Armor> equippedArmor;
    std::vector<std::unique_ptr<Item>> inventory;
    static constexpr size_t MAX_INVENTORY_SIZE = 8;
    std::pair<int, int> position;
public:
    explicit Player(const std::string& playerName);
    ~Player() = default;
    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;
    Player(Player&&) = default;
    Player& operator=(Player&&) = default;

    // Реализация виртуальных методов
    void attack(Entity& target);
    bool addItem(std::unique_ptr<Item> item);
    bool useItem(size_t itemIndex);
    int getHealth() const;
    void setHealth(int h);
    int getDamage() const;
    void setDamage(int d);
    void showInventory() const;
    int getInventorySize() const;
    std::optional<Item*> getItem(size_t itemIndex) const;
    int getLevel() const;
    void setLevel(int l);
    void removeItem(size_t index);
    int getCheckedRooms() const;
    void setCheckedRooms(int rooms);
    bool equipWeapon(std::unique_ptr<Weapon> weapon);
    bool equipArmor(std::unique_ptr<Armor> armor);
    void unequipWeapon();
    void unequipArmor();
    bool GetisDefending() const;
    void setDefending(bool defending);
    Armor* getEquippedArmor() const { return equippedArmor.get(); }
    Weapon* getEquippedWeapon() const { return equippedWeapon.get(); }
    int getTotalDamage() const;
    int getTotalDefense() const;
};

#endif // PLAYER_H