#include <iostream>
#include <random> 
#include <ctime>
#include <cmath>
#include <cstdlib>

//Функция: Выделение памяти 
void AllocateMatrix(int**& matrix, int size) {
    matrix = new int* [size];
    for (int i = 0; i < size; i++) {
        matrix[i] = new int[size];
    }
}

//Функция: Создание рандомного числа
int RandomNumber(int num_1, int num_2) {
    static std::mt19937 gen(std::random_device{}());
    if (num_1 > num_2) std::swap(num_1, num_2);
    std::uniform_int_distribution<int> dist(num_1, num_2);
    return dist(gen);
}

//Функция: Проверка на ввод
bool IsCorrectInput() {
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        return false;
    }
    return true;
}

//Функция: Проверка положительного числа
bool IsPositiveNumber(int number) {
    return number > 0;
}

//Функция: Вывод матрицы
void PrintMatrix(int** matrix, int size) {
    std::cout << "Вывод матрицы (" << size << "x" << size << "): \n";
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            std::cout << matrix[i][j];
            int abs_value = std::abs(matrix[i][j]);
            if (abs_value < 10) {
                std::cout << "     ";
            }
            else if (abs_value < 100) {
                std::cout << "    ";
            }
            else if (abs_value < 1000) {
                std::cout << "   ";
            }
            else if (abs_value < 10000) {
                std::cout << "  ";
            }
            else {
                std::cout << " ";
            }
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

//Функция: Удаление памяти 
void DeleteMatrix(int** matrix, int size) {
    if (matrix != nullptr) {
        for (int i = 0; i < size; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
}

//Функция: Заполнение матрицы вручную
void FillMatrixManually(int** matrix, int size) {
    std::cout << "Заполните матрицу " << size << "x" << size << ":\n";
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            std::cout << "Элемент [" << i << "][" << j << "]: ";
            std::cin >> matrix[i][j];
            if (!IsCorrectInput()) {
                std::cout << "Ошибка ввода!\n";
                return;
            }
        }
    }
}

//Функция: Заполнение матрицы случайными числами
void FillMatrixRandomly(int** matrix, int size) {
    int min_val, max_val;
    std::cout << "Введите минимальное значение: ";
    std::cin >> min_val;
    if (!IsCorrectInput()) {
        std::cout << "Ошибка ввода!\n";
        return;
    }
    std::cout << "Введите максимальное значение: ";
    std::cin >> max_val;
    if (!IsCorrectInput() || min_val > max_val) {
        std::cout << "Ошибка ввода!\n";
        return;
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] = RandomNumber(min_val, max_val);
        }
    }
    std::cout << "\n";
}

//Функция: Задание 1. Поиск максимального элемента в нижнем правом треугольнике матрицы
int FindMaxInLowerRightTriangle(int** matrix, int size) {
    if (matrix == nullptr || size == 0) return 0;
    int max_element = matrix[size - 1][size - 1];
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i + j >= size - 1) {
                if (matrix[i][j] > max_element) {
                    max_element = matrix[i][j];
                }
            }
        }
    }
    return max_element;
}

//Функция: Задание 2. Преобразование матрицы
void MoveMaxElement(int** matrix, int size) {
    int max_element = matrix[0][0];
    int max_element_col = 0;
    int max_element_row = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (matrix[i][j] > max_element) {
                max_element = matrix[i][j];
                max_element_col = i;
                max_element_row = j;
            }
        }
    }
    std::cout << "Максимальный элемент: " << max_element
        << " на позиции [" << max_element_col << "][" << max_element_row << "]\n";
    if (max_element_row != 0) {
        for (int i = 0; i < size; i++) {
            std::swap(matrix[i][0], matrix[i][max_element_row]);
        }
    }
    if (max_element_col != 0) {
        for (int j = 0; j < size; j++) {
            std::swap(matrix[0][j], matrix[max_element_col][j]);
        }
    }
}


int main() {
    setlocale(LC_ALL, "RUS");

    //Выбор способа заполнения матрицы
    int number;
    std::cout << "Создание целочисленной квадратной матрицы.\n"
        << "Для заполнения матрицы вручную выберите: 1\n"
        << "Для заполнения матрицы рандомайзером выберите: 2\n";
    std::cin >> number;
    if (!IsCorrectInput() || number < 1 || number > 2) {
        std::cout << "Ошибка, попробуйте еще раз!\n";
        return 0;
    }

    //Задаем размерность матрицы
    int size;
    std::cout << "Введите размер квадратной матрицы: ";
    std::cin >> size;
    if (!IsCorrectInput() || !IsPositiveNumber(size)) {
        std::cout << "Ошибка, попробуйте еще раз!\n";
        return 0;
    }

    //Выделение памяти
    int** matrix = nullptr;
    AllocateMatrix(matrix, size);

    //Заполнение матрицы выбранным способом
    if (number == 1) {
        FillMatrixManually(matrix, size);
    }
    else if (number == 2) {
        FillMatrixRandomly(matrix, size);
    }
    PrintMatrix(matrix, size);

    //Задание 1. Поиск максимального элемента нижнего правого треугольника
    int max_triangle = FindMaxInLowerRightTriangle(matrix, size);
    std::cout << "Максимальный элемент в нижнем правом треугольнике: " << max_triangle << "\n\n";

    //Задание 2. Преобразование
    MoveMaxElement(matrix, size);
    PrintMatrix(matrix, size);
    //Освобождение памяти
    DeleteMatrix(matrix, size);

    return 0;
}