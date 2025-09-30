#include <iostream>
#include <random>

//Функция: Проверка на ввод
bool is_correct_input(int num1) {
    if (std::cin.fail() || num1 <= 0) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        return false;
    }
    return true;
}

int main() {
    setlocale(LC_ALL, "RUS");
    //Ввод колличества элементов массива
    int size, num;
    std::cout << "Введите количество элементов массива: ";
    std::cin >> size;
    std::cout << "Для заполнения массива с клавиатуры введите 1\nДля заполнения массива случайными числами нажмите 2\n";
    std::cin >> num;
    //Создание, проверка и заполнение массива && проверка elements
    if (is_correct_input(size)) {
        int arr[100];
        if (num == 1) {
            for (int i = 0; i < size; i++) {
                std::cout << "Введите " << i + 1 << " элемент массива: ";
                std::cin >> arr[i];
                if (std::cin.fail()) {
                    std::cout << "\nОшибка, попробуйте еще раз";
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    return 0;
                }
            }
        }
        else if (num == 2) {
            int a, b;
            //Ввод границ интервала
            std::cout << "Введите нижнюю границу интервала a: ";
            std::cin >> a;
            std::cout << "Введите верхнюю границу интервала b: ";
            std::cin >> b;
            //Проверка корректности границ
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
        else {
            std::cout << "Ошибка, попробуйте еще раз\n";
            return 0;
        }
        // Находим количество перемен знаков
        int amount = 0;
        for (int i = 0; i < size - 1; i++) {
            if ((arr[i] <= -1 && arr[i + 1] >= 0) || (arr[i] >= 0 && arr[i + 1] <= -1)) {
                amount += 1;
            }
        }
        std::cout << "Количество перемен знаков: " << amount << "\n";
        // Находим первый 0
        int firstZeroIndex = -1;
        for (int i = 0; i < size; i++) {
            if (arr[i] == 0) {
                firstZeroIndex = i;
                break;
            }
        }
        //Находим второй 0
        int secondZeroIndex = -1;
        if (firstZeroIndex != -1) {
            for (int i = firstZeroIndex + 1; i < size; i++) {
                if (arr[i] == 0) {
                    secondZeroIndex = i;
                    break;
                }
            }
        }
        //Находим произведение
        int product = 1;
        if (firstZeroIndex != -1 && secondZeroIndex != -1) {
            if (secondZeroIndex - firstZeroIndex > 1) {
                for (int i = firstZeroIndex + 1; i < secondZeroIndex; i++) {
                    product *= arr[i];
                }
                std::cout << "Произведение чисел между нулями: " << product << "\n";
            }
            else {
                std::cout << "Между нулями нет чисел\n";
            }
        }
        else {
            std::cout << "В массиве меньше двух нулей\n";
        }
        //Преобразование массива
        for (int i = 0; i < size; i++) {
            if (arr[i] == 0) {
                //Передвигаем нули
                for (int j = i; j > 0; j--) {
                    std::swap(arr[j], arr[j - 1]);
                }
            }
            else if (arr[i] % 2 == 0) {
                //Передвигаем четные
                int pos = 0;
                while (pos < i && (arr[pos] == 0 || arr[pos] % 2 == 0)) {
                    pos++;
                }
                for (int j = i; j > pos; j--) {
                    std::swap(arr[j], arr[j - 1]);
                }
            }
        }
        // Вывод результата
        std::cout << "Преобразованный массив: ";
        for (int i = 0; i < size; i++) {
            std::cout << arr[i] << " ";
        }
        std::cout << "\n";
    }
    else {
        std::cout << "Ошибка, попробуйте еще раз\n";
    }
    return 0;
}