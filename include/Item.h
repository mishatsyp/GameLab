// Item.h
#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <memory>

class Player;

class Item {
protected:
    std::string name;
    std::string description;//!!!!
    int value;

public:
    Item(const std::string& itemName, const std::string& desc, int val);
    virtual ~Item() = default;

    virtual void use(Player& player) = 0;
    virtual std::string getStats() const = 0;
    virtual std::string getItemType() const = 0;
   // virtual std::unique_ptr<Item> clone() const = 0;


    const std::string& getName() const { return name; }
    const std::string& getDescription() const { return description; }
    int getValue() const { return value; }
};

// Potion.h
#ifndef POTION_H
#define POTION_H

#include "Item.h"

class Potion : public Item {
private:
    int healAmount;

public:
    Potion(int heal = 20);
    Potion(const std::string& potionName, int heal, int val);

    virtual void use(Player& player) override;
    virtual std::string getStats() const override;
    virtual std::string getItemType() const override;
    virtual std::unique_ptr<Item> clone() const override;

    int getHealAmount() const { return healAmount; }
};

#endif // POTION_H

// Weapon.h
#ifndef WEAPON_H
#define WEAPON_H

#include "Item.h"

class Weapon : public Item {
private:
    int damageBonus;
    int durability;
    static constexpr int MAX_DURABILITY = 100;

public:
    Weapon(const std::string& weaponName, int bonus);
    Weapon(const std::string& weaponName, int bonus, int dur, int val);

    virtual void use(Player& player) override;
    virtual std::string getStats() const override;
    virtual std::string getItemType() const override;
    virtual std::unique_ptr<Item> clone() const override;

    void reduceDurability(int amount = 5);
    bool isBroken() const { return durability <= 0; }
    int getDamageBonus() const { return damageBonus; }
    int getDurability() const { return durability; }
    int getMaxDurability() const { return MAX_DURABILITY; }
};

#endif // WEAPON_H

// Armor.h
#ifndef ARMOR_H
#define ARMOR_H

#include "Item.h"

class Armor : public Item {
private:
    int defenseBonus;
    int durability;
    static constexpr int MAX_DURABILITY = 100;

public:
    Armor(int bonus = 5);
    Armor(const std::string& armorName, int bonus, int dur, int val);

    virtual void use(Player& player) override;
    virtual std::string getStats() const override;
    virtual std::string getItemType() const override;
    virtual std::unique_ptr<Item> clone() const override;

    void reduceDurability(int amount = 5);
    int getDefenseBonus() const { return defenseBonus; }
    int getDurability() const { return durability; }
    int getMaxDurability() const { return MAX_DURABILITY; }
};

#endif // ARMOR_H

// Key.h (новый класс - ключи для выхода)
#ifndef KEY_H
#define KEY_H

#include "Item.h"

class Key : public Item {
private:
    std::string keyId;  // Уникальный ID ключа

public:
    Key(const std::string& keyName, const std::string& keyId);

    virtual void use(Player& player) override;
    virtual std::string getStats() const override;
    virtual std::string getItemType() const override;
    virtual std::unique_ptr<Item> clone() const override;

    const std::string& getKeyId() const { return keyId; }
};

#endif // KEY_H

#endif // ITEM_H
