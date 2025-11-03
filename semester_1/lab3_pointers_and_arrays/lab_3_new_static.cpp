#include <iostream>
#include <random>

// Функция: Создание рандомного числа
int GenerateRandomNumber(int min, int max) {
    static std::mt19937 gen(std::random_device{}());
    if (min > max) std::swap(min, max);
    std::uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}

// Функция: Заполнение массива вручную
void FillManually(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        std::cout << "Введите " << i + 1 << " элемент массива: ";
        std::cin >> arr[i];
        if (std::cin.fail()) {
            throw "Ошибка ввода! Введено не число при заполнении массива.";
        }
    }
}

// Функция: Заполнение массива рандомайзером
void FillRandomly(int* arr, int size, int min, int max) {
    for (int i = 0; i < size; i++) {
        arr[i] = GenerateRandomNumber(min, max);
    }
}

// Функция: Вывод массива
void PrintArray(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
}

// Функция: Подсчет количества перемен знака
int CountSignChanges(int* arr, int size) {
    int count = 0;
    for (int i = 0; i < size - 1; i++) {
        if ((arr[i] >= 0 && arr[i + 1] < 0) || (arr[i] < 0 && arr[i + 1] >= 0)) {
            count++;
        }
    }
    return count;
}

// Функция: Произведение чисел между первым и вторым нулями
int CalculateProductBetweenZeros(int* arr, int first_zero_index, int second_zero_index) {
    int product = 1;
    for (int i = first_zero_index + 1; i < second_zero_index; i++) {
        product *= arr[i];
    }
    return product;
}

// Функция: Поиск первого нуля
int FindFirstZeroIndex(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == 0) {
            return i;
        }
    }
    return -1;
}

// Функция: Поиск второго нуля
int FindSecondZeroIndex(int* arr, int size, int first_zero_index) {
    for (int i = first_zero_index + 1; i < size; i++) {
        if (arr[i] == 0) {
            return i;
        }
    }
    return -1;
}

// Функция: Преобразование массива
void TransformArray(int* arr, int size) {
    int write_index = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] == 0) {
            for (int j = i; j > write_index; j--) {
                std::swap(arr[j], arr[j - 1]);
            }
            write_index++;
        }
    }
    for (int i = write_index; i < size; i++) {
        if (arr[i] % 2 == 0) {
            int pos = write_index;
            while (pos < i&& arr[pos] % 2 == 0) {
                pos++;
            }
            for (int j = i; j > pos; j--) {
                std::swap(arr[j], arr[j - 1]);
            }
            write_index++;
        }
    }
}

int main() {
    try {
        setlocale(LC_ALL, "RUS");
        int arr[100];
        int size;

        // Ввод размера массива
        std::cout << "Введите количество элементов массива: ";
        std::cin >> size;

        if (std::cin.fail()) {
            throw "Ошибка! Вы ввели не число для размера массива.";
        }
        if (size < 1) {
            throw "Ошибка! Количество элементов массива не должно быть меньше 1.";
        }
        if (size > 100) {
            throw "Ошибка! Количество элементов массива не должно быть больше 100.";
        }

        // Выбор способа заполнения
        int choice;
        std::cout << "\nДля заполнения массива вручную введите 1\nДля заполнения массива рандомайзером введите 2\nВыберите способ заполнения массива: ";
        std::cin >> choice;
        std::cout << "\n";

        if (std::cin.fail()) {
            throw "Ошибка! Вы ввели не число для выбора способа заполнения.";
        }
        if (choice < 1 || choice > 2) {
            throw "Ошибка! Введено неверное число для выбора способа заполнения.";
        }

        // Заполнение массива
        if (choice == 1) {
            FillManually(arr, size);
        }
        else {
            int min, max;
            std::cout << "Введите минимальный элемент массива: ";
            std::cin >> min;
            if (std::cin.fail()) {
                throw "Ошибка! Вы ввели не число для минимального элемента.";
            }
            std::cout << "Введите максимальный элемент массива: ";
            std::cin >> max;
            if (std::cin.fail()) {
                throw "Ошибка! Вы ввели не число для максимального элемента.";
            }
            if (min > max) {
                throw "Ошибка! Минимальный элемент массива больше максимального.";
            }
            FillRandomly(arr, size, min, max);
        }

        // Вывод исходного массива
        std::cout << "\nВывод массива:\n";
        PrintArray(arr, size);

        // Задание 1: Подсчет перемен знака
        int signChanges = CountSignChanges(arr, size);
        std::cout << "\nЗадание 1) Количество перемен знака: " << signChanges << "\n\n";

        // Задание 2: Произведение между нулям
        try {
            int first_zero_index = FindFirstZeroIndex(arr, size);
            int second_zero_index = FindSecondZeroIndex(arr, size, first_zero_index);

            if (first_zero_index == -1) {
                throw "В массиве нет нулей!";
            }
            else if (second_zero_index == -1) {
                throw "В массиве только один ноль!";
            }
            else if (second_zero_index == first_zero_index + 1) {
                throw "Между нулями нет чисел!";
            }
            else {
                int product = CalculateProductBetweenZeros(arr, first_zero_index, second_zero_index);
                std::cout << "Задание 2) Произведение элементов массива между первым и вторым нулем равно: " << product << "\n";
            }
        }
        catch (const char* msg) {
            std::cout << "Задание 2) " << msg << "\n";
        }

        // Задание 3: Преобразование массива
        std::cout << "\nЗадание 3) Преобразование массива...\n";
        TransformArray(arr, size);
        std::cout << "Преобразованный массив:\n";
        PrintArray(arr, size);

    }
    catch (const char* msg) {
        std::cout << "\n" << msg << "\n";
        return 1;
    }

    return 0;
}