#include <random>
class Random {
private:
    std::mt19937 rng;

    // Приватный конструктор (синглтон)
    Random();

public:
    // Запрещаем копирование и перемещение
    Random(const Random&) = delete;
    Random(Random&&) = delete;
    Random& operator=(const Random&) = delete;
    Random& operator=(Random&&) = delete;

    // Статический метод для получения экземпляра
    static Random& getInstance();

    /**
     * @brief Получение случайного числа в диапазоне
     * @param min минимальное значение
     * @param max максимальное значение
     * @return случайное число
     */
    int getInt(int min, int max);

    /**
     * @brief Получение случайного числа с плавающей точкой
     * @param min минимальное значение
     * @param max максимальное значение
     * @return случайное число
     */
    double getDouble(double min, double max);

    /**
     * @brief Получение случайного булевого значения
     * @param probability вероятность true (0.0 - 1.0)
     * @return true/false
     */
    bool getBool(double probability = 0.5);

    /**
     * @brief Выбор случайного элемента из вектора
     * @param vec вектор
     * @return std::optional - элемент или nullopt если вектор пуст
     */
    template<typename T>
    std::optional<T> getRandomElement(const std::vector<T>& vec) {
        if (vec.empty()) {
            return std::nullopt;
        }
        std::uniform_int_distribution<size_t> dist(0, vec.size() - 1);
        return vec[dist(rng)];
    }

    /**
     * @brief Перемешивание контейнера
     * @param container контейнер для перемешивания
     */
    template<typename Container>
    void shuffle(Container& container) {
        std::shuffle(container.begin(), container.end(), rng);
    }
};

#endif // RANDOM_H