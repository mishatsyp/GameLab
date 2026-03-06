#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <memory>
#include "Item.h"

class Player;

class Item {
protected:
    std::string name;
    int durability;
public:
    Item(const std::string& itemName);
    virtual ~Item() = default;

    virtual void use(Player& player) = 0;
    virtual std::string getStats() const = 0;
    virtual std::string getItemType() const = 0;
    virtual int getItemDurability() const=0;
   // virtual std::unique_ptr<Item> clone() const = 0;

    const std::string& getName() const { return name; }
};





class Potion : public Item {
private:
    int healAmount;
public:
    Potion(int heal = 20);
    Potion(const std::string& potionName, int heal, int dur);
    virtual void use(Player& player) override;
    virtual std::string getStats() const override; //сколько раз может отхилить
   // virtual std::unique_ptr<Item> clone() const override;

    int getHealAmount() const { return healAmount; } //сколько хилит в целом
};

class Weapon : public Item {
private:
    int damage;
    static constexpr int MAX_DURABILITY = 100;

public:
    Weapon(const std::string& weaponName, int damage);
    Weapon(const std::string& weaponName, int damage, int dur);

    virtual void use(Player& player) override;
    virtual std::string getStats() const override; //возвращает урон меча
    // virtual std::string getItemType() const override;//тип пред
    // virtual std::unique_ptr<Item> clone() const override;

    void reduceDurability(int amount = 5);
    bool isBroken() const { return durability <= 0; }
    int getDamage() const { return damage; }
    int getDurability() const { return durability; }
    // int getMaxDurability() const { return MAX_DURABILITY; }
};


class Armor : public Item {
private:
    int defense;
    int durability;
    static constexpr int MAX_DURABILITY = 100;

public:
    Armor(int bonus = 5);
    Armor(const std::string& armorName, int defen, int dur);
    virtual void use(Player& player) override;
    virtual std::string getStats() const override; // - возвращает durability
    virtual std::string getItemType() const override;
    // virtual std::unique_ptr<Item> clone() const override;

    void reduceDurability(int amount = 5);
    int getDefense() const { return defense; }
    int getDurability() const { return durability; }
    // int getMaxDurability() const { return MAX_DURABILITY; }
};

#endif