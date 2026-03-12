#include <gtest/gtest.h>
#include "Player.h"
#include "Item.h"
#include <memory>

// Тест 1: Создание игрока
TEST(PlayerTest, CreatePlayer) {
    Player player("Hero");

    EXPECT_EQ(player.getHealth(), 100);
    EXPECT_EQ(player.getDamage(), 10);
    EXPECT_EQ(player.getLevel(), 1);
    EXPECT_EQ(player.getInventorySize(), 0);
    EXPECT_EQ(player.getTotalDamage(), 10); // Без оружия
    EXPECT_EQ(player.getTotalDefense(), 0); // Без брони
}

// Тест 2: Добавление предметов в инвентарь
TEST(PlayerTest, AddItem) {
    Player player("Hero");

    auto potion = std::make_unique<Potion>("Health Potion", 20, 1);
    auto weapon = std::make_unique<Weapon>("Sword", 15, 100);

    EXPECT_TRUE(player.addItem(std::move(potion)));
    EXPECT_TRUE(player.addItem(std::move(weapon)));
    EXPECT_EQ(player.getInventorySize(), 2);
}

// Тест 3: Лимит инвентаря (MAX_INVENTORY_SIZE)
// TEST(PlayerTest, InventoryLimit) {
//     Player player("Hero");
//
//     // Пытаемся добавить больше предметов, чем позволяет инвентарь
//     for (int i = 0; i < 20; ++i) { // MAX_INVENTORY_SIZE = 10?
//         auto item = std::make_unique<Potion>("Potion", 20, 1);
//         bool added = player.addItem(std::move(item));
//
//         if (i < 10) { // Если лимит 10
//             EXPECT_TRUE(added);
//         } else {
//             EXPECT_FALSE(added);
//         }
//     }
// }

// Тест 4: Получение предмета из инвентаря
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

// Тест 5: Использование предмета
// TEST(PlayerTest, UseItem) {
//     Player player("Hero");
//     int initialHealth = player.getHealth();
//
//     auto potion = std::make_unique<Potion>("Health Potion", 20, 1);
//     player.addItem(std::move(potion));
//
//     EXPECT_TRUE(player.useItem(0));
//     EXPECT_GT(player.getHealth(), initialHealth); // Здоровье должно увеличиться
// }

// Тест 6: Удаление предмета
TEST(PlayerTest, RemoveItem) {
    Player player("Hero");

    auto potion = std::make_unique<Potion>("Health Potion", 20, 1);
    player.addItem(std::move(potion));
    EXPECT_EQ(player.getInventorySize(), 1);

    player.removeItem(0);
    EXPECT_EQ(player.getInventorySize(), 0);
}

// Тест 7: Экипировка оружия
// TEST(PlayerTest, EquipWeapon) {
//     Player player("Hero");
//     int baseDamage = player.getDamage();
//
//     auto sword = std::make_shared<Weapon>("Sword", 15, 100);
//     player.addItem(std::unique_ptr<Item>(sword.get())); // Проблема: дублирование владения
//
//     // Правильный способ:
//     auto weaponPtr = std::make_shared<Weapon>("Sword", 15, 100);
//     EXPECT_TRUE(player.equipWeapon(weaponPtr));
//
//     EXPECT_EQ(player.getTotalDamage(), baseDamage + 15);
// }

// Тест 8: Экипировка брони
// TEST(PlayerTest, EquipArmor) {
//     Player player("Hero");
//
//     auto armorPtr = std::make_shared<Armor>("Plate Armor", 10, 100);
//     EXPECT_TRUE(player.equipArmor(armorPtr));
//
//     EXPECT_EQ(player.getTotalDefense(), 10);
// }

// Тест 9: Смена экипировки
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

// Тест 10: Защита (isDefending)
TEST(PlayerTest, Defending) {
    Player player("Hero");

    EXPECT_FALSE(player.GetisDefending());

    player.setDefending(true);
    EXPECT_TRUE(player.GetisDefending());

    player.setDefending(false);
    EXPECT_FALSE(player.GetisDefending());
}

// Тест 11: Уровни и исследованные комнаты
TEST(PlayerTest, LevelAndRooms) {
    Player player("Hero");

    EXPECT_EQ(player.getLevel(), 1);
    EXPECT_EQ(player.getCheckedRooms(), 0);

    player.setLevel(3);
    player.setCheckedRooms(5);

    EXPECT_EQ(player.getLevel(), 3);
    EXPECT_EQ(player.getCheckedRooms(), 5);
}

// Тест 12: Здоровье не может быть отрицательным (проверка логики setHealth)
// TEST(PlayerTest, HealthBounds) {
//     Player player("Hero");
//
//     player.setHealth(-50);
//     // Если в setHealth есть защита от отрицательных значений
//     // EXPECT_GE(player.getHealth(), 0);
//
//     // Если нет защиты, то проверим что сеттер работает
//     EXPECT_EQ(player.getHealth(), -50); // или другая логика
// }