#include <gtest/gtest.h>
#include <sstream>
#include <iostream>
#include "../include/Item.h"
#include "../include/Player.h"


TEST(ItemTest, Constructor) {}

TEST(PotionTest, Constructor) {
    Potion potion(30);
    EXPECT_EQ(potion.getName(), "Зелье здоровья");
    EXPECT_EQ(potion.getHealAmount(), 30);
    EXPECT_EQ(potion.getItemDurability(), 3);
    EXPECT_EQ(potion.getItemType(), "Potion");
}

TEST(PotionTest, CustomConstructor) {
    Potion potion("Magic Potion", 50, 5);
    EXPECT_EQ(potion.getName(), "Magic Potion");
    EXPECT_EQ(potion.getHealAmount(), 50);
    EXPECT_EQ(potion.getItemDurability(), 5);
    EXPECT_EQ(potion.getItemType(), "Potion");
}

TEST(PotionTest, Use) {
    Player player("TestPlayer");
    player.setHealth(50);
    Potion potion(30);

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    potion.use(player);

    EXPECT_EQ(player.getHealth(), 80);
    EXPECT_EQ(potion.getItemDurability(), 2);

    std::string output = buffer.str();
    EXPECT_NE(output.find("восстановили"), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(PotionTest, UseWhenEmpty) {
    Player player("TestPlayer");
    player.setHealth(50);
    Potion potion("Empty Potion", 30, 0);

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    potion.use(player);

    EXPECT_EQ(player.getHealth(), 50);
    EXPECT_EQ(potion.getItemDurability(), 0);

    std::string output = buffer.str();
    EXPECT_NE(output.find("закончилось"), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(PotionTest, GetStats) {
    Potion potion("Health Potion", 25, 3);
    std::string stats = potion.getStats();
    EXPECT_NE(stats.find("+25"), std::string::npos);
    EXPECT_NE(stats.find("3"), std::string::npos);
}

TEST(WeaponTest, Constructor) {
    Weapon weapon("Steel Sword", 15);
    EXPECT_EQ(weapon.getName(), "Steel Sword");
    EXPECT_EQ(weapon.getDamage(), 15);
    EXPECT_EQ(weapon.getItemDurability(), 100);
    EXPECT_EQ(weapon.getItemType(), "Weapon");
}

TEST(WeaponTest, CustomConstructor) {
    Weapon weapon("Iron Axe", 20, 75);
    EXPECT_EQ(weapon.getName(), "Iron Axe");
    EXPECT_EQ(weapon.getDamage(), 20);
    EXPECT_EQ(weapon.getItemDurability(), 75);
}

TEST(WeaponTest, ReduceDurability) {
    Weapon weapon("Test Weapon", 10, 50);

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    weapon.reduceDurability(30);
    EXPECT_EQ(weapon.getItemDurability(), 20);

    weapon.reduceDurability(25);
    EXPECT_EQ(weapon.getItemDurability(), 0);

    std::string output = buffer.str();
    EXPECT_NE(output.find("сломалось"), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(WeaponTest, Use) {
    Player player("TestPlayer");
    Weapon weapon("Test Sword", 15);

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    weapon.use(player);

    std::string output = buffer.str();
    EXPECT_NE(output.find("экипировали"), std::string::npos);
    EXPECT_NE(output.find("Test Sword"), std::string::npos);
    EXPECT_NE(output.find("+15"), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(WeaponTest, GetStats) {
    Weapon weapon("Dragon Slayer", 50, 80);
    std::string stats = weapon.getStats();
    EXPECT_NE(stats.find("+50"), std::string::npos);
    EXPECT_NE(stats.find("80/100"), std::string::npos);
}


TEST(ArmorTest, Use) {
    Player player("TestPlayer");
    Armor armor("Steel Plate", 20, 100);

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    armor.use(player);

    std::string output = buffer.str();
    EXPECT_NE(output.find("надели"), std::string::npos);
    EXPECT_NE(output.find("Steel Plate"), std::string::npos);
    EXPECT_NE(output.find("+20"), std::string::npos);

    std::cout.rdbuf(old);
}


TEST(ItemTest, Polymorphism) {
    std::vector<std::shared_ptr<Item>> items;

    items.push_back(std::make_shared<Potion>("Healing", 30, 3));
    items.push_back(std::make_shared<Weapon>("Sword", 15, 100));
    items.push_back(std::make_shared<Armor>("Shield", 10, 100));

    EXPECT_EQ(items[0]->getItemType(), "Potion");
    EXPECT_EQ(items[1]->getItemType(), "Weapon");
    EXPECT_EQ(items[2]->getItemType(), "Armor");

    Player player("TestPlayer");
    player.setHealth(50);

    EXPECT_NO_THROW(items[0]->use(player));
    EXPECT_NO_THROW(items[1]->use(player));
    EXPECT_NO_THROW(items[2]->use(player));
}