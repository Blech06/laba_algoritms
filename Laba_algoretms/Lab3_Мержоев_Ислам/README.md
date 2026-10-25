# Лабораторная работа №3

**Тема:** Реализация динамического массива (аналог `std::vector`). Итераторы  

**Уровень:** Средний  
**Вариант:** 4 — методы `min()` и `max()`

**Студент:** Мержоев Ислам Игоревич  
**Группа:** ПИЖ-б-о-25-1  

---

## Цель работы

Реализовать шаблонный класс `Vector<T>` — аналог `std::vector` — с нуля.  
Освоить управление динамической памятью, закрепить «правило пяти», реализовать методы `min()` и `max()`.

---

## Выполнение

### 1. Структура класса

```cpp
template <typename T>
class Vector {
private:
    T* data;        // указатель на динамический массив
    int sz;         // текущий размер
    int cap;        // ёмкость

public:
    // Конструкторы
    Vector();
    explicit Vector(int n);
    Vector(int n, const T& val);
    Vector(const Vector& other);      // копирования
    Vector(Vector&& other) noexcept;  // перемещения

    // Деструктор
    ~Vector();

    // Операторы присваивания
    Vector& operator=(const Vector& other);
    Vector& operator=(Vector&& other) noexcept;

    // Доступ
    T& operator[](int index);
    const T& operator[](int index) const;
    int size() const;
    int capacity() const;
    bool empty() const;

    // Изменение
    void push_back(const T& value);
    void pop_back();
    void reserve(int newCap);
    void resize(int newSize, const T& defaultValue = T());
    void clear();
    void swap(Vector& other) noexcept;

    // Вариант 4
    T min() const;
    T max() const;

    // Итераторы
    T* begin();
    T* end();
    const T* begin() const;
    const T* end() const;
};
```

### 2. Конструкторы и деструктор

```cpp
// Конструктор по умолчанию
Vector() : data(nullptr), sz(0), cap(0) {}

// Конструктор с размером
explicit Vector(int n) : sz(n), cap(n) {
    data = new T[cap];
    for (int i = 0; i < sz; ++i)
        data[i] = T();
}

// Конструктор копирования (глубокое копирование)
Vector(const Vector& other) : sz(other.sz), cap(other.cap) {
    data = new T[cap];
    for (int i = 0; i < sz; ++i)
        data[i] = other.data[i];
}

// Конструктор перемещения
Vector(Vector&& other) noexcept
    : data(other.data), sz(other.sz), cap(other.cap) {
    other.data = nullptr;
    other.sz = 0;
    other.cap = 0;
}

// Деструктор
~Vector() {
    delete[] data;
}
```

### 3. Операторы присваивания (правило пяти)

```cpp
// Копирующее присваивание (copy-and-swap)
Vector& operator=(const Vector& other) {
    if (this != &other) {
        Vector temp(other);
        swap(temp);
    }
    return *this;
}

// Перемещающее присваивание
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
```

### 4. push_back с удвоением ёмкости

```cpp
void push_back(const T& value) {
    if (sz >= cap) {
        int newCap = (cap == 0) ? 1 : cap * 2;
        reallocate(newCap);
    }
    data[sz++] = value;
}
```

Стратегия удвоения даёт **амортизированную сложность O(1)**.

### 5. Методы min() и max() (вариант 4)

```cpp
// O(n)
T min() const {
    if (empty())
        throw std::runtime_error("Vector is empty");

    T result = data[0];
    for (int i = 1; i < sz; ++i)
        if (data[i] < result)
            result = data[i];
    return result;
}

// O(n)
T max() const {
    if (empty())
        throw std::runtime_error("Vector is empty");

    T result = data[0];
    for (int i = 1; i < sz; ++i)
        if (data[i] > result)
            result = data[i];
    return result;
}
```

### 6. Итераторы

```cpp
T* begin() { return data; }
T* end()   { return data + sz; }
const T* begin() const { return data; }
const T* end()   const { return data + sz; }
```

Позволяют использовать range-based for:

```cpp
for (int x : v) {
    cout << x << " ";
}
```

---

## Анализ сложности

| Операция                | Сложность            | Пояснение                    |
|-------------------------|----------------------|------------------------------|
| `push_back`             | O(1) амортизированно | Удвоение ёмкости             |
| `pop_back`              | O(1)                 | Уменьшение size              |
| `operator[]`            | O(1)                 | Прямой доступ                |
| `min()` / `max()`       | O(n)                 | Линейный проход              |
| Конструктор копирования | O(n)                 | Глубокое копирование         |
| Конструктор перемещения | O(1)                 | Передача указателя           |
| `reserve` / `resize`    | O(n)                 | Копирование элементов        |

---

## Как запустить

```bash
# Перейти в папку с исходниками
cd src

# Компиляция
g++ -std=c++17 -Wall -Wextra -o vector_demo main.cpp

# Запуск
./vector_demo
```

---

## Пример вывода программы

```
=== Лабораторная работа №3 ===
Средний уровень. Вариант 4: Vector с методами min() и max()

1. Создание пустого вектора
   size = 0, capacity = 0

2. Добавление элементов через push_back:
   push_back(7)  -> size=1, capacity=1
   push_back(14) -> size=2, capacity=2
   ...
   push_back(10) -> size=10, capacity=16

3. Содержимое вектора: [7, 14, 1, 8, 15, 2, 9, 16, 3, 10]

4. Методы min() и max() (вариант 4):
   Минимальный элемент: 1
   Максимальный элемент: 16

7. Демонстрация правила пяти:
   v2 (копия v): [7, 14, 1, 8, 15, 2, 9, 16, 3]
   v4 = move(v2): [7, 14, 1, 8, 15, 2, 9, 16, 3]
   v2 после move: size=0

9. Обработка ошибок:
   Исключение при min() на пустом векторе: Vector is empty
   Исключение при выходе за границы: Index out of range
```

---

## Вывод

В ходе лабораторной работы:

1. Реализован шаблонный класс `Vector<T>` с нуля.
2. Реализовано полное **правило пяти** (деструктор, копирование и перемещение).
3. Реализовано динамическое управление памятью со стратегией удвоения ёмкости.
4. Добавлены методы `min()` и `max()` согласно варианту 4.
5. Добавлены итераторы для поддержки range-based for.
6. Реализована корректная обработка ошибок через исключения.

Освоены: работа с динамической памятью, амортизированный анализ, move-семантика, шаблоны классов.

---
