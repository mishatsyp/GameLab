#include <gtest/gtest.h>
#include "Player.h"
#include "Item.h"
#include <memory>

TEST(PlayerTest, CreatePlayer) {
    Player player("Hero");

    EXPECT_EQ(player.getHealth(), 100);
    EXPECT_EQ(player.getDamage(), 10);
    EXPECT_EQ(player.getLevel(), 1);
    EXPECT_EQ(player.getInventorySize(), 0);
    EXPECT_EQ(player.getTotalDamage(), 10);
    EXPECT_EQ(player.getTotalDefense(), 0);
}

TEST(PlayerTest, AddItem) {
    Player player("Hero");

    auto potion = std::make_unique<Potion>("Health Potion", 20, 1);
    auto weapon = std::make_unique<Weapon>("Sword", 15, 100);

    EXPECT_TRUE(player.addItem(std::move(potion)));
    EXPECT_TRUE(player.addItem(std::move(weapon)));
    EXPECT_EQ(player.getInventorySize(), 2);
}

TEST(PlayerTest, GetItem) {
    Player player("Hero");

    auto potion = std::make_unique<Potion>("Health Potion", 20, 1);
    player.addItem(std::move(potion));

    auto item = player.getItem(0);
    EXPECT_TRUE(item.has_value());
    EXPECT_EQ(item.value()->getName(), "Health Potion");

    // Несуществующий индекс
    auto invalidItem = player.getItem(999);
    EXPECT_FALSE(invalidItem.has_value());
}

TEST(PlayerTest, RemoveItem) {
    Player player("Hero");

    auto potion = std::make_unique<Potion>("Health Potion", 20, 1);
    player.addItem(std::move(potion));
    EXPECT_EQ(player.getInventorySize(), 1);

    player.removeItem(0);
    EXPECT_EQ(player.getInventorySize(), 0);
}

TEST(PlayerTest, EquipWeapon) {
    Player player("Hero");
    int baseDamage = player.getDamage();

    auto sword = std::make_shared<Weapon>("Sword", 15, 100);
    player.addItem(std::unique_ptr<Item>(sword.get())); // Проблема: дублирование владения

    auto weaponPtr = std::make_shared<Weapon>("Sword", 15, 100);
    EXPECT_TRUE(player.equipWeapon(weaponPtr));

    EXPECT_EQ(player.getTotalDamage(), baseDamage + 15);
}

TEST(PlayerTest, EquipArmor) {
    Player player("Hero");

    auto armorPtr = std::make_shared<Armor>("Plate Armor", 10, 100);
    EXPECT_TRUE(player.equipArmor(armorPtr));

    EXPECT_EQ(player.getTotalDefense(), 10);
}

TEST(PlayerTest, ChangeEquipment) {
    Player player("Hero");

    auto sword1 = std::make_shared<Weapon>("Sword", 15, 100);
    auto sword2 = std::make_shared<Weapon>("Greatsword", 25, 100);

    player.equipWeapon(sword1);
    EXPECT_EQ(player.getTotalDamage(), player.getDamage() + 15);

    // Меняем оружие
    player.equipWeapon(sword2);
    EXPECT_EQ(player.getTotalDamage(), player.getDamage() + 25);

    // Старое оружие должно быть в инвентаре
    EXPECT_EQ(player.getInventorySize(), 1);
    auto oldWeapon = player.getItem(0);
    EXPECT_TRUE(oldWeapon.has_value());
    EXPECT_EQ(oldWeapon.value()->getName(), "Sword");
}

TEST(PlayerTest, Defending) {
    Player player("Hero");

    EXPECT_FALSE(player.GetisDefending());

    player.setDefending(true);
    EXPECT_TRUE(player.GetisDefending());

    player.setDefending(false);
    EXPECT_FALSE(player.GetisDefending());
}

TEST(PlayerTest, LevelAndRooms) {
    Player player("Hero");

    EXPECT_EQ(player.getLevel(), 1);
    EXPECT_EQ(player.getCheckedRooms(), 0);

    player.setLevel(3);
    player.setCheckedRooms(5);

    EXPECT_EQ(player.getLevel(), 3);
    EXPECT_EQ(player.getCheckedRooms(), 5);
}