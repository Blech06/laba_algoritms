#ifndef VECTOR_H
#define VECTOR_H

#include <stdexcept>
#include <utility>   // std::swap
#include <iostream>

template <typename T>
class Vector {
private:
    T* data;        // указатель на динамический массив
    int sz;         // текущий размер (количество элементов)
    int cap;        // ёмкость (выделенная память)

    // Вспомогательный метод расширения
    void reallocate(int newCap) {
        T* newData = new T[newCap];
        for (int i = 0; i < sz; ++i) {
            newData[i] = std::move(data[i]);
        }
        delete[] data;
        data = newData;
        cap = newCap;
    }

public:
    // ===================== Конструкторы =====================

    // Конструктор по умолчанию
    Vector() : data(nullptr), sz(0), cap(0) {}

    // Конструктор с размером
    explicit Vector(int n) : sz(n), cap(n) {
        if (n < 0) throw std::invalid_argument("Size cannot be negative");
        data = new T[cap];
        for (int i = 0; i < sz; ++i) {
            data[i] = T();
        }
    }

    // Конструктор с размером и значением
    Vector(int n, const T& val) : sz(n), cap(n) {
        if (n < 0) throw std::invalid_argument("Size cannot be negative");
        data = new T[cap];
        for (int i = 0; i < sz; ++i) {
            data[i] = val;
        }
    }

    // Конструктор копирования (глубокое копирование)
    Vector(const Vector& other) : sz(other.sz), cap(other.cap) {
        data = new T[cap];
        for (int i = 0; i < sz; ++i) {
            data[i] = other.data[i];
        }
    }

    // Конструктор перемещения
    Vector(Vector&& other) noexcept
        : data(other.data), sz(other.sz), cap(other.cap) {
        other.data = nullptr;
        other.sz = 0;
        other.cap = 0;
    }

    // ===================== Деструктор =====================
    ~Vector() {
        delete[] data;
    }

    // ===================== Операторы присваивания =====================

    // Оператор присваивания копированием (copy-and-swap)
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            Vector temp(other);   // создаём копию
            swap(temp);           // обмениваем
        }
        return *this;
    }

    // Оператор присваивания перемещением
    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            sz = other.sz;
            cap = other.cap;
            other.data = nullptr;
            other.sz = 0;
            other.cap = 0;
        }
        return *this;
    }

    // ===================== Доступ по индексу =====================
    T& operator[](int index) {
        if (index < 0 || index >= sz)
            throw std::out_of_range("Index out of range");
        return data[index];
    }

    const T& operator[](int index) const {
        if (index < 0 || index >= sz)
            throw std::out_of_range("Index out of range");
        return data[index];
    }

    // ===================== Методы доступа =====================
    int size() const { return sz; }
    int capacity() const { return cap; }
    bool empty() const { return sz == 0; }

    // ===================== Основные методы изменения =====================

    void push_back(const T& value) {
        if (sz >= cap) {
            int newCap = (cap == 0) ? 1 : cap * 2;
            reallocate(newCap);
        }
        data[sz++] = value;
    }

    void pop_back() {
        if (empty())
            throw std::underflow_error("Vector is empty");
        --sz;
    }

    void reserve(int newCap) {
        if (newCap > cap) {
            reallocate(newCap);
        }
    }

    void resize(int newSize, const T& defaultValue = T()) {
        if (newSize < 0)
            throw std::invalid_argument("Size cannot be negative");

        if (newSize > cap) {
            reallocate(newSize);
        }
        if (newSize > sz) {
            for (int i = sz; i < newSize; ++i) {
                data[i] = defaultValue;
            }
        }
        sz = newSize;
    }

    void clear() {
        sz = 0;
    }

    void swap(Vector& other) noexcept {
        std::swap(data, other.data);
        std::swap(sz, other.sz);
        std::swap(cap, other.cap);
    }

    // ===================== Вариант 4: min / max =====================

    // Возвращает минимальный элемент. Сложность: O(n)
    T min() const {
        if (empty())
            throw std::runtime_error("Vector is empty");

        T result = data[0];
        for (int i = 1; i < sz; ++i) {
            if (data[i] < result) {
                result = data[i];
            }
        }
        return result;
    }

    // Возвращает максимальный элемент. Сложность: O(n)
    T max() const {
        if (empty())
            throw std::runtime_error("Vector is empty");

        T result = data[0];
        for (int i = 1; i < sz; ++i) {
            if (data[i] > result) {
                result = data[i];
            }
        }
        return result;
    }

    // ===================== Итераторы (для удобства) =====================
    T* begin() { return data; }
    T* end() { return data + sz; }
    const T* begin() const { return data; }
    const T* end() const { return data + sz; }

    // ===================== Вывод =====================
    void print() const {
        std::cout << "[";
        for (int i = 0; i < sz; ++i) {
            std::cout << data[i];
            if (i < sz - 1) std::cout << ", ";
        }
        std::cout << "]";
    }
};

#endif // VECTOR_H
