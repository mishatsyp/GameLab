#ifndef RANDOM_H
#define RANDOM_H

#pragma once
#include <random>
#include <optional>
#include <algorithm>

class Random {
private:
    std::mt19937 rng;
    Random();
public:
    Random(const Random&) = delete;
    Random(Random&&) = delete;
    Random& operator=(const Random&) = delete;
    Random& operator=(Random&&) = delete;
    static Random& getInstance();

    int getInt(int min, int max);

    double getDouble(double min, double max);

    bool getBool(double probability = 0.5);

    template<typename T>
    std::optional<T> getRandomElement(const std::vector<T>& vec) {
        if (vec.empty()) {
            return std::nullopt;
        }
        std::uniform_int_distribution<size_t> dist(0, vec.size() - 1);
        return vec[dist(rng)];
    }

    // перемешивать
    template<typename Container>
    void shuffle(Container& container) {
        std::shuffle(container.begin(), container.end(), rng);
    }
};

#endif // RANDOM_H