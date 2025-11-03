#include <iostream>
#include <random>
#include <cmath>

// Функция: Проверка на ввод
bool is_correct_input(int num) {
    if (std::cin.fail() || num <= 0) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        return false;
    }
    return true;
}

// Функция: Заполнение массива с клавиатуры
void FillManually(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        std::cout << "Введите " << i + 1 << " элемент массива: ";
        std::cin >> arr[i];
        if (std::cin.fail()) {
            throw "Ошибка ввода! Введено не число при заполнении массива.";
        }
    }
}

// Функция: Заполнение массива случайными числами
void FillRandomly(int* arr, int size) {
    int a, b;
    std::cout << "Введите нижнюю границу интервала a: ";
    std::cin >> a;
    if (std::cin.fail()) {
        throw "Ошибка! Введено не число для нижней границы.";
    }

    std::cout << "Введите верхнюю границу интервала b: ";
    std::cin >> b;
    if (std::cin.fail()) {
        throw "Ошибка! Введено не число для верхней границы.";
    }

    if (a > b) {
        throw "Ошибка! Нижняя граница не может быть больше верхней.";
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(a, b);

    // Заполнение массива случайными числами
    for (int i = 0; i < size; i++) {
        arr[i] = dist(gen);
    }

    // Вывод сгенерированного массива
    std::cout << "Сгенерированный массив: ";
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
}

// Функция: Поиск максимального по модулю элемента
int FindMaxAbsolute(int* arr, int size) {
    if (size == 0) {
        throw "Ошибка! Массив пуст.";
    }

    int max = std::abs(arr[0]);
    for (int i = 1; i < size; i++) {
        if (std::abs(arr[i]) > max) {
            max = std::abs(arr[i]);
        }
    }
    return max;
}

// Функция: Сумма элементов после первого положительного
int SumAfterFirstPositive(int* arr, int size) {
    bool positiveFound = false;
    int firstPositiveIndex = -1;

    // Находим индекс первого положительного элемента
    for (int i = 0; i < size; i++) {
        if (arr[i] > 0) {
            firstPositiveIndex = i;
            positiveFound = true;
            break;
        }
    }

    if (!positiveFound) {
        throw "В массиве нет положительных элементов.";
    }

    // Если первый положительный элемент последний
    if (firstPositiveIndex == size - 1) {
        return 0;
    }

    // Считаем сумму элементов после первого положительного
    int sum = 0;
    for (int i = firstPositiveIndex + 1; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

// Функция: Преобразование массива
void TransformArray(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        if (arr[i] >= 0 && arr[i] <= 10) {
            int insertPos = 0;
            while (insertPos < i && arr[insertPos] >= 0 && arr[insertPos] <= 10) {
                insertPos++;
            }
            if (insertPos < i) {
                for (int j = i; j > insertPos; j--) {
                    std::swap(arr[j], arr[j - 1]);
                }
            }
        }
    }
}

// Функция: Вывод массива
void PrintArray(int* arr, int size) {
    std::cout << "Массив: ";
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
}

int main() {
    try {
        setlocale(LC_ALL, "RUS");

        // Ввод количества элементов массива
        int size;
        std::cout << "Введите количество элементов массива: ";
        std::cin >> size;

        if (!is_correct_input(size)) {
            throw "Ошибка! Некорректный размер массива.";
        }

        // Создание динамического массива
        int* arr = new int[size];

        try {
            // Выбор способа заполнения
            int choice;
            std::cout << "Для заполнения массива с клавиатуры введите 1\nДля заполнения массива случайными числами нажмите 2\n";
            std::cin >> choice;

            if (std::cin.fail()) {
                throw "Ошибка! Некорректный выбор способа заполнения.";
            }

            if (choice == 1) {
                FillManually(arr, size);
            }
            else if (choice == 2) {
                FillRandomly(arr, size);
            }
            else {
                throw "Ошибка! Неверный выбор. Введите 1 или 2.";
            }

            // Вывод исходного массива
            std::cout << "\nИсходный ";
            PrintArray(arr, size);

            // Задание 1: Максимальный по модулю элемент
            try {
                int maxAbs = FindMaxAbsolute(arr, size);
                std::cout << "1) Максимальный по модулю элемент массива: " << maxAbs << "\n";
            }
            catch (const char* msg) {
                std::cout << "1) " << msg << "\n";
            }

            // Задание 2: Сумма после первого положительного
            try {
                int sum = SumAfterFirstPositive(arr, size);
                std::cout << "2) Сумма элементов массива после первого положительного: " << sum << "\n";
            }
            catch (const char* msg) {
                std::cout << "2) " << msg << "\n";
            }

            // Задание 3: Преобразование массива
            std::cout << "3) Преобразование массива...\n";
            TransformArray(arr, size);
            std::cout << "Преобразованный ";
            PrintArray(arr, size);

        }
        catch (const char* msg) {
            delete[] arr;
            throw;
        }

        // Освобождение памяти
        delete[] arr;

    }
    catch (const char* msg) {
        std::cout << "\n" << msg << "\n";
        return 1;
    }

    return 0;
}