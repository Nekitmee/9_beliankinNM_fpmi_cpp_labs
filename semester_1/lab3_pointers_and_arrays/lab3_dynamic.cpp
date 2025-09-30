#include <iostream>
#include <random>
#include <cmath>

//Функция: Проверка на ввод
bool is_correct_input(int num1) {
    if (std::cin.fail() || num1 <= 0) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        return false;
    }
    return true;
}

int main()
{
    setlocale(LC_ALL, "RUS");
    //Ввод колличества элементов массива
    int size, num;
    std::cout << "Введите количество элементов массива: ";
    std::cin >> size;
    if (is_correct_input(size)) {
        //Создание динамического массива и выбор способа заполнения
        int* arr = new int[size];
        std::cout << "Для заполнения массива с клавиатуры введите 1\nДля заполнения массива случайными числами нажмите 2\n";
        std::cin >> num;
        //Заполнение с клавиатуры
        if (num == 1) {
            for (int i = 0; i < size; i++) {
                std::cout << "Введите " << i + 1 << " элемент массива: ";
                std::cin >> arr[i];
                if (std::cin.fail()) {
                    std::cout << "\nОшибка, попробуйте еще раз!";
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    return 0;
                }
            }
        }
        //Заполнение рандомайзером
        else if (num == 2) {
            int a, b;
            //Ввод границ интервала и проверка корректности границ
            std::cout << "Введите нижнюю границу интервала a: ";
            std::cin >> a;
            std::cout << "Введите верхнюю границу интервала b: ";
            std::cin >> b;
            if (std::cin.fail() || a > b) {
                std::cout << "Ошибка ввода границ интервала!\n";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                return 0;
            }
            //Инициализация генератора случайных чисел
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<int> dist(a, b);
            //Заполнение массива случайными числами
            for (int i = 0; i < size; i++) {
                arr[i] = dist(gen);
            }
            //Вывод сгенерированного массива
            std::cout << "Сгенерированный массив: ";
            for (int i = 0; i < size; i++) {
                std::cout << arr[i] << " ";
            }
            std::cout << "\n";
        }
        //Ошибка при вводе num
        else {
            std::cout << "Ошибка, попробуйте еще раз!\n";
        }
        //1) Создание переменной для хранения максимального по модулю значения массива, поиск и вывод его
        int max = 0;
        for (int i = 0; i < size; i++) {
            if (std::abs(arr[i]) > max) {
                max = std::abs(arr[i]);
            }
        }
        std::cout << "Максимальный по модулю элемент массива: " << max << "\n";
        //2) Сумма элементов массива расположенных после первого положительного
        int summ = 0;
        bool positiveFound = false;
        for (int i = 0; i < size; i++) {
            if (arr[i] > 0) {
                positiveFound = true;
                for (int j = i + 1; j < size; j++) {
                    summ += arr[j];
                }
                break;
            }
        }
        if (positiveFound) {
            std::cout << "Сумма элементов массива после первого положительного: " << summ << "\n";
        }
        else {
            std::cout << "В массиве нет положительных элементов\n";
        }
        //3) Преобразование массива
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
        //Вывод преобразованного массива
        std::cout << "Преобразованный массив: ";
        for (int i = 0; i < size; i++) {
            std::cout << arr[i] << " ";
        }
        std::cout << "\n";
        delete[] arr;
        return 0;
    }
    //Ошибка при вводе size
    else {
        std::cout << "Ошибка, попробуйте еще раз!\n";
    }
}
