#include "../include/Player.h"
#include "../include/Item.h"      // <-- ЭТО ДОБАВИТЬ!
#include "../include/Screen.h"

Player::Player(const std::string& playerName)
    : name(playerName), inBattle(false), health(100), damage(10),
      level(1), checked_rooms(0), isDefending(false) {}

void Player::attack(Entity &target) {target.takeDamage(damage);}

bool Player::addItem(std::shared_ptr<Item> item) {
    if (inventory.size() < MAX_INVENTORY_SIZE) {
        inventory.push_back(std::move(item));
        return true;
    }
    return false;
}

bool Player::useItem(const size_t itemIndex) {
    if (itemIndex < inventory.size()) {
        if (inventory[itemIndex]) {
            inventory[itemIndex]->use(*this);
            return true;
        }
    }
    return false;
}

void Player::showInventory() const {Screen::drawInventory(*this);}

int Player::getInventorySize() const {return inventory.size();}

std::optional<std::shared_ptr<Item>> Player::getItem(size_t itemIndex) const {
    if (itemIndex < inventory.size() && inventory[itemIndex]) {
        return inventory[itemIndex];
    }
    return std::nullopt;
}

int Player::getHealth() const {return health;}
void Player::setHealth(int h) {
    health = h;
    if (health > MAX_HEALTH) {
        health = MAX_HEALTH;
    }
    if (health < 0) health = 0;
}
int Player::getDamage() const {return damage;}
void Player::setDamage(int d) {damage = d;}
int Player::getLevel() const {return level;}
void Player::setLevel(int l) {level=l;}
void Player::removeItem(size_t index) {
    if (index < inventory.size()) {inventory.erase(inventory.begin() + static_cast<int>(index));}
}

void Player::setCheckedRooms(int rooms){checked_rooms=rooms;}
int Player::getCheckedRooms() const {return checked_rooms;}
bool Player::equipWeapon(std::shared_ptr<Weapon> weapon) {
    if (!weapon) return false;
    if (equippedWeapon) {
        inventory.push_back(equippedWeapon);
    }
    equippedWeapon = weapon;
    return true;
}

bool Player::equipArmor(std::shared_ptr<Armor> armor) {
    if (!armor) return false;

    if (equippedArmor) {
        inventory.push_back(equippedArmor);
    }

    equippedArmor = armor;
    return true;
}

int Player::getTotalDamage() const {
    int total = damage;
    if (equippedWeapon) {
        total += equippedWeapon->getDamage();
    }
    return total;
}

int Player::getTotalDefense() const {
    int total = 0;
    if (equippedArmor) {
        total += equippedArmor->getDefense();
    }
    return total;
}

void Player::setDefending(bool defending) {
    isDefending = defending;
}

void Player::unequipWeapon() {
    if (equippedWeapon) {
        inventory.push_back(equippedWeapon);
        equippedWeapon = nullptr;
    }
}

void Player::unequipArmor() {
    if (equippedArmor) {
        inventory.push_back(equippedArmor);
        equippedArmor = nullptr;
    }
}

bool Player::GetisDefending() const {return  isDefending;}
