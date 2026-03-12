#include <gtest/gtest.h>
#include "Random.h"

// Тест 1: Проверка getInt в диапазоне
TEST(RandomTest, GetIntInRange) {
    Random& rng = Random::getInstance();

    int min = 5;
    int max = 10;
    int result = rng.getInt(min, max);

    EXPECT_GE(result, min);
    EXPECT_LE(result, max);
}

// Тест 2: Проверка getDouble в диапазоне
TEST(RandomTest, GetDoubleInRange) {
    Random& rng = Random::getInstance();

    double min = 1.5;
    double max = 3.7;
    double result = rng.getDouble(min, max);

    EXPECT_GE(result, min);
    EXPECT_LE(result, max);
}

// Тест 3: Проверка getBool с вероятностью
TEST(RandomTest, GetBoolProbability) {
    Random& rng = Random::getInstance();

    // Тест с вероятностью 1.0 (всегда true)
    EXPECT_TRUE(rng.getBool(1.0));

    // Тест с вероятностью 0.0 (всегда false)
    EXPECT_FALSE(rng.getBool(0.0));
}

// Тест 4: Проверка getRandomElement с вектором
TEST(RandomTest, GetRandomElementFromVector) {
    Random& rng = Random::getInstance();

    std::vector<int> vec = {10, 20, 30, 40, 50};
    auto result = rng.getRandomElement(vec);

    ASSERT_TRUE(result.has_value());
    EXPECT_NE(std::find(vec.begin(), vec.end(), result.value()), vec.end());
}

// Тест 5: Проверка getRandomElement с пустым вектором
TEST(RandomTest, GetRandomElementFromEmptyVector) {
    Random& rng = Random::getInstance();

    std::vector<int> emptyVec;
    auto result = rng.getRandomElement(emptyVec);

    EXPECT_FALSE(result.has_value());
}

// Тест 6: Проверка shuffle контейнера
TEST(RandomTest, ShuffleContainer) {
    Random& rng = Random::getInstance();

    std::vector<int> original = {1, 2, 3, 4, 5};
    std::vector<int> shuffled = original;

    rng.shuffle(shuffled);

    // Проверяем, что размер не изменился
    EXPECT_EQ(original.size(), shuffled.size());

    // Проверяем, что все элементы присутствуют (хотя порядок мог измениться)
    for (int val : original) {
        EXPECT_NE(std::find(shuffled.begin(), shuffled.end(), val), shuffled.end());
    }
}