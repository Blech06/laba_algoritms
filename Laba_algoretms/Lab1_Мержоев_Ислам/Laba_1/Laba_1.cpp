#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <chrono>
#include <string>
#include <stdexcept>
#include <clocale>

using namespace std;
using namespace chrono;
// ============================================================
// 1. Реализация на std::map (O(log n))
// ============================================================
template <typename T>
class CounterMap {
private:
    map<T, int> counts;

public:
    // O(log n)
    void add(const T& value) {
        counts[value]++;
    }

    // O(log n)
    int getCount(const T& value) const {
        auto it = counts.find(value);
        return (it != counts.end()) ? it->second : 0;
    }

    // O(n)
    void reset() {
        counts.clear();
    }

    // O(n)
    T getMostFrequent() const {
        if (counts.empty()) {
            throw runtime_error("Counter is empty");
        }
        T mostFreq = counts.begin()->first;
        int maxCount = counts.begin()->second;
        for (const auto& pair : counts) {
            if (pair.second > maxCount) {
                maxCount = pair.second;
                mostFreq = pair.first;
            }
        }
        return mostFreq;
    }

    size_t size() const { return counts.size(); }
};

// ============================================================
// 2. Реализация на std::unordered_map (амортизированно O(1))
// ============================================================
template <typename T>
class CounterHash {
private:
    unordered_map<T, int> counts;

public:
    // Амортизированно O(1)
    void add(const T& value) {
        counts[value]++;
    }

    // Амортизированно O(1)
    int getCount(const T& value) const {
        auto it = counts.find(value);
        return (it != counts.end()) ? it->second : 0;
    }

    // O(n)
    void reset() {
        counts.clear();
    }

    // O(n)
    T getMostFrequent() const {
        if (counts.empty()) {
            throw runtime_error("Counter is empty");
        }
        T mostFreq = counts.begin()->first;
        int maxCount = counts.begin()->second;
        for (const auto& pair : counts) {
            if (pair.second > maxCount) {
                maxCount = pair.second;
                mostFreq = pair.first;
            }
        }
        return mostFreq;
    }

    size_t size() const { return counts.size(); }
};

// Функция измерения времени
template <typename Func>
long long measureTime(Func func) {
    auto start = high_resolution_clock::now();
    func();
    auto end = high_resolution_clock::now();
    return duration_cast<microseconds>(end - start).count();
}

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "=== Средний уровень. Вариант 4: Counter<T> ===\n\n";

    // Демонстрация работы
    cout << "1. Демонстрация работы CounterHash<string>:\n";
    CounterHash<string> counter;

    vector<string> words = {
        "яблоко", "груша", "яблоко", "банан", "яблоко",
        "груша", "апельсин", "банан", "яблоко", "груша"
    };

    for (const auto& w : words) {
        counter.add(w);
    }

    cout << "Количество 'яблоко': " << counter.getCount("яблоко") << endl;
    cout << "Количество 'груша':  " << counter.getCount("груша") << endl;
    cout << "Количество 'киви':   " << counter.getCount("киви") << endl;
    cout << "Самый частый элемент: " << counter.getMostFrequent() << endl;
    cout << "Уникальных элементов: " << counter.size() << endl;

    counter.reset();
    cout << "После reset() размер: " << counter.size() << "\n\n";

    // Экспериментальное сравнение
    cout << "2. Экспериментальное сравнение производительности\n";
    const int N = 100000;
    const int SEARCHES = 10000;

    vector<int> data(N);
    for (int i = 0; i < N; i++) data[i] = i % 1000;

    long long timeMapAdd = measureTime([&]() {
        CounterMap<int> cm;
        for (int x : data) cm.add(x);
        });

    CounterMap<int> cm;
    for (int x : data) cm.add(x);
    long long timeMapGet = measureTime([&]() {
        for (int i = 0; i < SEARCHES; i++) cm.getCount(i % 1000);
        });

    long long timeHashAdd = measureTime([&]() {
        CounterHash<int> ch;
        for (int x : data) ch.add(x);
        });

    CounterHash<int> ch;
    for (int x : data) ch.add(x);
    long long timeHashGet = measureTime([&]() {
        for (int i = 0; i < SEARCHES; i++) ch.getCount(i % 1000);
        });

    cout << "add 100000 элементов (map):            " << timeMapAdd << " мкс\n";
    cout << "add 100000 элементов (unordered_map):  " << timeHashAdd << " мкс\n";
    cout << "getCount 10000 раз (map):              " << timeMapGet << " мкс\n";
    cout << "getCount 10000 раз (unordered_map):    " << timeHashGet << " мкс\n";

    return 0;
}
