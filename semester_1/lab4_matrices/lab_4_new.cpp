#include <iostream>
#include <random>
#include <cmath>

int RandomNumber(int min, int max);
void AllocateMatrix(int**& matrix, int size);
void DeleteMatrix(int** matrix, int size);
void PrintMatrix(int** matrix, int size);
void FillMatrixManually(int** matrix, int size);
void FillMatrixRandomly(int** matrix, int size);
int FindMaxInLowerRightTriangle(int** matrix, int size);
void MoveMaxElement(int** matrix, int size);

int main()
{
    try {
        setlocale(LC_ALL, "RU");
        int number;
        std::cout << "Создание целочисленной квадратной матрицы.\n"
            << "Для заполнения матрицы вручную выберите: 1\n"
            << "Для заполнения матрицы рандомайзером выберите: 2\n";
        std::cin >> number;
        if (std::cin.fail() || number < 1 || number > 2) {
            throw "Ошибка, попробуйте еще раз!\n";
        }
        int size;
        std::cout << "Введите размер квадратной матрицы: ";
        std::cin >> size;
        if (std::cin.fail() || size < 1) {
           throw "Ошибка, попробуйте еще раз!\n";
        }
        int** matrix = nullptr;
        AllocateMatrix(matrix, size);
        if (number == 1) {
            FillMatrixManually(matrix, size);
        }
        else if (number == 2) {
            FillMatrixRandomly(matrix, size);
        }
        PrintMatrix(matrix, size);
        std::cout << "Максимальный элемент в нижнем правом треугольнике: " << FindMaxInLowerRightTriangle(matrix, size) << "\n\n";
        MoveMaxElement(matrix, size);
        PrintMatrix(matrix, size);
        DeleteMatrix(matrix, size);
        return 0;
    }
    catch (const int* msg) {
        std::cout << msg;
    }
}

// Функция: Создание рандомного числа 
int RandomNumber(int min, int max) {
    static std::mt19937 gen(std::random_device{}());
    if (min > max) std::swap(min, max);
    std::uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}

// Функция: Выделение памяти 
void AllocateMatrix(int**& matrix, int size) {
    matrix = new int* [size];
    for (int i = 0; i < size; i++) {
        matrix[i] = new int[size]();
    }
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

//Функция: Вывод матрицы
void PrintMatrix(int** matrix, int size) {
    std::cout << "Вывод матрицы (" << size << "x" << size << "): \n";
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            std::cout << matrix[i][j];
            int value = matrix[i][j];
            int total_length = 0;
            if (value < 0) {
                total_length = 1;
            }
            int temp = std::abs(value);
            if (temp == 0) {
                total_length = 1;
            }
            else {
                while (temp > 0) {
                    total_length++;
                    temp /= 10;
                }
            }
            if (total_length < 2) std::cout << "     ";
            else if (total_length < 3) std::cout << "    ";
            else if (total_length < 4) std::cout << "   ";
            else if (total_length < 5) std::cout << "  ";
            else if (total_length < 6) std::cout << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

//Функция: Заполнение матрицы вручную
void FillMatrixManually(int** matrix, int size) {
    std::cout << "Заполните матрицу " << size << "x" << size << ":\n";
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            std::cout << "Элемент [" << i << "][" << j << "]: ";
            std::cin >> matrix[i][j];
            if (std::cin.fail()) {
                throw "Ошибка, попробуйте еще раз!\n";
            }
        }
    }
}

//Функция: Заполнение матрицы случайными числами
void FillMatrixRandomly(int** matrix, int size) {
    int min_val, max_val;
    std::cout << "Введите минимальное значение: ";
    std::cin >> min_val;
    if (std::cin.fail()) {
        throw "Ошибка, попробуйте еще раз!\n";
    }
    std::cout << "Введите максимальное значение: ";
    std::cin >> max_val;
    if (std::cin.fail()) {
        throw "Ошибка, попробуйте еще раз!\n";
    }
    if (max_val < min_val) {
        throw "Ошибка, попробуйте еще раз!\n";
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