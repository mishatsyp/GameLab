#include "../include/Player.h"
#include "../include/Item.h"      // <-- ЭТО ДОБАВИТЬ!
#include "../include/Screen.h"

Player::Player(const std::string& playerName)
    : name( playerName ), inBattle( false ),
    health( 100 ), damage( 10 ) {}

void Player::attack(Entity &target) {
    target.takeDamage(damage);
}

bool Player::addItem(std::unique_ptr<Item> item) { // зачем bool
    if (inventory.size() < MAX_INVENTORY_SIZE) {
        inventory.push_back(std::move(item));
        return true;
    }
    return false;
}

bool Player::useItem(const size_t itemIndex) {
    if (itemIndex < inventory.size()) {
        if (inventory[itemIndex]) {
            // inventory[itemIndex] -> use(); ???
            return true;
        }
    }
    return false;
}

void Player::showInventory() const {
    Screen::drawInventory(*this);
}

int Player::getInventorySize() const {
    return inventory.size();
}

Item* Player::getItem(size_t itemIndex) const {
    if (itemIndex < inventory.size()) {
        if (inventory[itemIndex]) {
            return inventory[itemIndex].get();
        }
    }
    return nullptr;
}

int Player::getHealth() const {
    return health;
}

void Player::setHealth(int h) {
    health = h;
}

int Player::getDamage() const {
    return damage;
}

void Player::setDamage(int d) {
    damage = d;
}

int Player::getLevel() const {
    return level;
}

void Player::setLevel(int l) {
    level=l;
}

void Player::removeItem(size_t index) {
    if (index < inventory.size()) {
        inventory.erase(inventory.begin() + static_cast<int>(index));
    }
}