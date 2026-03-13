#include "../include/Item.h"

Item::Item(const std::string& itemName, const int dur) : name(itemName), durability(dur) {}
Potion::Potion(int heal) : Item("Зелье здоровья", 3), healAmount(heal) {}
Potion::Potion(const std::string& potionName, int heal, int dur) : Item(potionName, dur), healAmount(heal) {}
void Potion::use(Player& player) {
    if (durability > 0) {
        durability--;
        player.setHealth(player.getHealth()+healAmount);
        std::cout << "Вы выпили " << name << " и восстановили " << healAmount << " здоровья.\n";
    } else {
        std::cout << "Зелье закончилось!\n";
    }
}

std::string Potion::getStats() const {
    return "Зелье лечения +" + std::to_string(healAmount) + " HP | Осталось использований: " + std::to_string(durability);
}

std::string Potion::getItemType() const {
    return "Potion";
}

int Potion::getItemDurability() const {
    return durability;
}
Weapon::Weapon(const std::string& weaponName, int damage) : Item(weaponName, 100), damage(damage) {}

Weapon::Weapon(const std::string& weaponName, int damage, int dur)
    : Item(weaponName, dur), damage(damage) {
    if (dur <= 0) durability = 30;
}

std::string Weapon::getStats() const {
    return "Урон: +" + std::to_string(damage) + " | Прочность: " + std::to_string(durability) + "/100";
}

std::string Weapon::getItemType() const {
    return "Weapon";
}

int Weapon::getItemDurability() const {
    return durability;
}

void Weapon::reduceDurability(int amount) {
    durability -= amount;
    if (durability < 0) durability = 0;
    if (durability == 0) {
        std::cout << name << " сломалось!\n";
    }
}



Armor::Armor(int defense) : Item("Броня", 20), defense(defense) {}

Armor::Armor(const std::string& armorName, int def, int dur): Item(armorName, dur), defense(def) {
    if (dur <= 0) durability = 30;
}


std::string Armor::getStats() const {
    return "Защита: +" + std::to_string(defense) + " | Прочность: " + std::to_string(durability) + "/100";
}

std::string Armor::getItemType() const {
    return "Armor";
}

int Armor::getItemDurability() const {
    return durability;
}

void Armor::reduceDurability(int amount) {
    durability -= amount;
    if (durability < 0) durability = 0;
    if (durability == 0) {
        std::cout << name << " разрушена!\n";
    }
}

void Weapon::use(Player& player) {
    player.equipWeapon(std::make_unique<Weapon>(*this));  // экипируем копию
    std::cout << "Вы экипировали " << name << " (урон +" << damage << ")\n";
}
void Armor::use(Player& player) {
    std::cout << "Вы надели " << name << " (защита +" << defense << ")\n";
    player.equipArmor(std::make_unique<Armor>(*this));  // экипируем копию
}