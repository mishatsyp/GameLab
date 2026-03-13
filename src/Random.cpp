#include "../include/Random.h"
#include <ctime>

Random::Random() {
    rng.seed(static_cast<unsigned int>(std::time(nullptr)));
}

Random& Random::getInstance() {
    static Random instance;
    return instance;
}

int Random::getInt(int min, int max) {
    if (min > max) {
        std::swap(min, max);
    }
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}

double Random::getDouble(double min, double max) {
    if (min > max) {
        std::swap(min, max);
    }
    std::uniform_real_distribution<double> dist(min, max);
    return dist(rng);
}


bool Random::getBool(double probability) {
    if (probability <= 0.0) return false;
    if (probability >= 1.0) return true;
    std::bernoulli_distribution dist(probability);
    return dist(rng);
}