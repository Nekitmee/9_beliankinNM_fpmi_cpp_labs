#include <iostream>
#include <ctime>

//Функция: Провеерка ввода
bool IsInputCorrect() {
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        return false;
    }
    return true;
}

//Функция: Создание массива с помощью ввода 
int* CreateArray_1(int size) {
    int* arr = new int[size];
    for (int i = 0; i < size; i++) {
        std::cout << "Введите " << i + 1 << " член массива: ";
        std::cin >> arr[i];
        if (!IsInputCorrect()) {
            delete[] arr;
            return nullptr;
        }
    }
    return arr;
}

//Функция: Создание массива с помощью рандомайзера
int* CreateArray_2(int size, int min, int max) {
    int* arr = new int[size];
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % (max - min + 1) + min;
    }
    return arr;
}

//Функция: Вывод массива
void PrintArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        std::cout << i + 1 << " элемент массива: " << arr[i] << "\n";
    }
}

//Функция: Поиск максимального элемента 
int SearchMaxElement(int arr[], int size) {
    int MaxElement = arr[0];
    for (int i = 0; i < size; i++) {
        if (arr[i] > MaxElement) {
            MaxElement = arr[i];
        }
    }
    return MaxElement;
}

int main() {
    setlocale(LC_ALL, "RUS");
    srand(time(NULL));

    //Создание, заполнение и проверка переменной "size"
    int size;
    std::cout << "Введите размер массива: ";
    std::cin >> size;
    if (!IsInputCorrect() || size < 1) {
        std::cout << "Ошибка ввода\n";
        return 0;
    }

    //Создание, заполнение и проверка переменной "number"
    int number;
    std::cout << "Для заполнения массива вручную введите 1\nДля заполнения массива рандомайзером введите 2\n";
    std::cin >> number;
    if (!IsInputCorrect() || number < 1 || number > 2) {
        std::cout << "Ошибка ввода\n";
        return 0;
    }

    int* arr = nullptr;  //Объявляем указатель

    //Ввод массива с клавиатуры
    if (number == 1) {
        arr = CreateArray_1(size); 
        if (arr == nullptr) { 
            std::cout << "Ошибка ввода\n";
            return 0;
        }
    }

    //Ввод массива рандомайзером
    else if (number == 2) {
        int min, max;
        std::cout << "Введите нижнюю границу: ";
        std::cin >> min;
        if (!IsInputCorrect()) {
            std::cout << "Ошибка ввода\n";
            return 0;
        }
        std::cout << "Введите верхнюю границу: ";
        std::cin >> max;
        if (!IsInputCorrect() || min > max) { //Можно добавть проверку: max - min < 1
            std::cout << "Ошибка ввода\n";
            return 0;
        }
        arr = CreateArray_2(size, min, max); 
    }

    //Выводим массив и находим максимальный элемент
    PrintArray(arr, size);
    int MaxElement = SearchMaxElement(arr, size);
    std::cout << "Максимальный элемент массива: " << MaxElement << "\n";
    delete[] arr;
    return 0;
}