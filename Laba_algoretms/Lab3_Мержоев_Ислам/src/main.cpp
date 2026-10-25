#include <iostream>
#include <clocale>
#include "Vector.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "=== Лабораторная работа №3 ===" << endl;
    cout << "Средний уровень. Вариант 4: Vector с методами min() и max()\n" << endl;

    // 1. Создание и заполнение
    Vector<int> v;
    cout << "1. Создание пустого вектора" << endl;
    cout << "   size = " << v.size() << ", capacity = " << v.capacity() << endl;

    cout << "\n2. Добавление элементов через push_back:" << endl;
    for (int i = 1; i <= 10; ++i) {
        v.push_back(i * 7 % 20);   // немного "случайные" значения
        cout << "   push_back(" << (i * 7 % 20) << ") -> size=" << v.size()
             << ", capacity=" << v.capacity() << endl;
    }

    cout << "\n3. Содержимое вектора: ";
    v.print();
    cout << endl;

    // 2. Демонстрация min / max (вариант 4)
    cout << "\n4. Методы min() и max() (вариант 4):" << endl;
    cout << "   Минимальный элемент: " << v.min() << endl;
    cout << "   Максимальный элемент: " << v.max() << endl;

    // 3. Другие операции
    cout << "\n5. Доступ по индексу: v[3] = " << v[3] << endl;

    v.pop_back();
    cout << "\n6. После pop_back(): ";
    v.print();
    cout << " (size=" << v.size() << ")" << endl;

    // 4. Демонстрация правила пяти
    cout << "\n7. Демонстрация правила пяти:" << endl;

    Vector<int> v2 = v;               // конструктор копирования
    cout << "   v2 (копия v): ";
    v2.print();
    cout << endl;

    Vector<int> v3;
    v3 = v;                           // оператор присваивания копированием
    cout << "   v3 = v: ";
    v3.print();
    cout << endl;

    Vector<int> v4 = std::move(v2);   // конструктор перемещения
    cout << "   v4 = move(v2): ";
    v4.print();
    cout << endl;
    cout << "   v2 после move (должен быть пустым): size=" << v2.size() << endl;

    // 5. Работа с другими типами
    cout << "\n8. Работа с double:" << endl;
    Vector<double> vd;
    vd.push_back(3.14);
    vd.push_back(1.41);
    vd.push_back(2.71);
    vd.push_back(1.73);
    cout << "   Вектор: ";
    vd.print();
    cout << "\n   min = " << vd.min() << ", max = " << vd.max() << endl;

    // 6. Обработка ошибок
    cout << "\n9. Обработка ошибок:" << endl;
    try {
        Vector<int> empty;
        empty.min();
    } catch (const exception& e) {
        cout << "   Исключение при min() на пустом векторе: " << e.what() << endl;
    }

    try {
        cout << v[100] << endl;
    } catch (const exception& e) {
        cout << "   Исключение при выходе за границы: " << e.what() << endl;
    }

    cout << "\n=== Программа завершена успешно ===" << endl;
    return 0;
}
