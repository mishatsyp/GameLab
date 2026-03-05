#include "../include/Random.h"
#include <ctime>

// Приватный конструктор инициализирует генератор случайных чисел
Random::Random() {
    // Используем традиционный time(nullptr) для инициализации
    rng.seed(static_cast<unsigned int>(std::time(nullptr)));
}

// Статический метод для получения экземпляра синглтона
Random& Random::getInstance() {
    static Random instance;  // Инициализируется при первом вызове
    return instance;
}

// Получение случайного целого числа в диапазоне [min, max]
int Random::getInt(int min, int max) {
    if (min > max) {
        std::swap(min, max);
    }
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}

// Получение случайного числа с плавающей точкой в диапазоне [min, max]
double Random::getDouble(double min, double max) {
    if (min > max) {
        std::swap(min, max);
    }
    std::uniform_real_distribution<double> dist(min, max);
    return dist(rng);
}

// Получение случайного булевого значения с заданной вероятностью
bool Random::getBool(double probability) {
    // Ограничиваем вероятность диапазоном [0.0, 1.0]
    if (probability <= 0.0) return false;
    if (probability >= 1.0) return true;
    std::bernoulli_distribution dist(probability);
    return dist(rng);
}