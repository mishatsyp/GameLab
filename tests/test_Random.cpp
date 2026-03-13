#include <gtest/gtest.h>
#include "Random.h"

TEST(RandomTest, GetIntInRange) {
    Random& rng = Random::getInstance();
    int min = 5;
    int max = 10;
    int result = rng.getInt(min, max);
    EXPECT_GE(result, min);
    EXPECT_LE(result, max);
}

TEST(RandomTest, GetDoubleInRange) {
    Random& rng = Random::getInstance();
    double min = 1.5;
    double max = 3.7;
    double result = rng.getDouble(min, max);
    EXPECT_GE(result, min);
    EXPECT_LE(result, max);
}

TEST(RandomTest, GetBoolProbability) {
    Random& rng = Random::getInstance();
    EXPECT_TRUE(rng.getBool(1.0));
    EXPECT_FALSE(rng.getBool(0.0));
}

TEST(RandomTest, GetRandomElementFromVector) {
    Random& rng = Random::getInstance();
    std::vector<int> vec = {10, 20, 30, 40, 50};
    auto result = rng.getRandomElement(vec);
    ASSERT_TRUE(result.has_value());
    EXPECT_NE(std::find(vec.begin(), vec.end(), result.value()), vec.end());
}

TEST(RandomTest, GetRandomElementFromEmptyVector) {
    Random& rng = Random::getInstance();
    std::vector<int> emptyVec;
    auto result = rng.getRandomElement(emptyVec);
    EXPECT_FALSE(result.has_value());
}

TEST(RandomTest, ShuffleContainer) {
    Random& rng = Random::getInstance();
    std::vector<int> original = {1, 2, 3, 4, 5};
    std::vector<int> shuffled = original;
    rng.shuffle(shuffled);
    EXPECT_EQ(original.size(), shuffled.size());
    for (int val : original) {
        EXPECT_NE(std::find(shuffled.begin(), shuffled.end(), val), shuffled.end());
    }
}