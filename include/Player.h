#ifndef PLAYER_H
#define PLAYER_H

#pragma once
#include <string>
#include <vector>
#include <memory>
#include <optional>
#include "Entity.h"


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
    int MAX_HEALTH = 100;
    std::shared_ptr<Weapon> equippedWeapon;
    std::shared_ptr<Armor> equippedArmor;
    std::vector<std::shared_ptr<Item>> inventory;
    static constexpr size_t MAX_INVENTORY_SIZE = 8;
    std::pair<int, int> position;
public:
    explicit Player(const std::string& playerName);
    ~Player() = default;
    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;
    Player(Player&&) = default;
    Player& operator=(Player&&) = default;

    void attack(Entity& target);

    bool addItem(std::shared_ptr<Item> item);
    bool useItem(size_t itemIndex);
    std::optional<std::shared_ptr<Item>> getItem(size_t itemIndex) const;
    void removeItem(size_t index);
    int getInventorySize() const;
    void showInventory() const;

    bool equipWeapon(std::shared_ptr<Weapon> weapon);
    bool equipArmor(std::shared_ptr<Armor> armor);

    std::shared_ptr<Weapon> getEquippedWeapon() const { return equippedWeapon; }
    std::shared_ptr<Armor> getEquippedArmor() const { return equippedArmor; }

    bool GetisDefending() const;
    void setDefending(bool defending);

    int getHealth() const;
    void setHealth(int h);
    int getDamage() const;
    void setDamage(int d);
    int getLevel() const;
    void setLevel(int l);
    int getCheckedRooms() const;
    void setCheckedRooms(int rooms);

    int getTotalDamage() const;
    int getTotalDefense() const;
    void unequipWeapon();
    void unequipArmor();
};

#endif // PLAYER_H