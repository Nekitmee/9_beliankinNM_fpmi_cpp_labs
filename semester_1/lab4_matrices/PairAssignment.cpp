#include <iostream>
#include <random> 
#include <ctime>

//Функция: Создание рандомного числа
int RandomNumber(int num_1, int num_2) {
	static std::mt19937 gen(std::random_device{}());
	if (num_1 > num_2) std::swap(num_1, num_2);
	std::uniform_int_distribution<int> dist(num_1, num_2);
	return dist(gen);
}

//Функция: Проверка ввода
bool IsCorrectInput() {
	if (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		return false;
	}
	else {
		return true;
	}
}

//Функция: Выделение памяти 
void MemoryAllocation(int**& matrix, int rows, int cols) {
	matrix = new int* [rows];
	for (int i = 0; i < rows; i++) {
		matrix[i] = new int[cols];
	}
}

//Функция: Заполнение матрицы вручную
void FillingManually(int**& matrix, int rows, int cols) {
	std::cout << "Заполнение матрицы:\n\n";
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			std::cout << "Введите [" << i << "][" << j << "] элемент матрицы: ";
			std::cin >> matrix[i][j];
		}
	}
}

//Функция: Заполнение матрицы рандомайзером
void FillingRandomly(int**& matrix, int rows, int cols, int min, int max) {
	std::cout << "\n";
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			matrix[i][j] = RandomNumber(min, max);
		}
	}
}

//Функция: Вывод матрицы
void PrintMatrix(int** matrix, int rows, int cols) {
	std::cout << "Вывод матрицы: \n";
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
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
void MemoryDelete(int** matrix, int rows) {
	for (int i = 0; i < rows; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
}

//Функция: сортировка вставками (1)
void InsertionSort(int**& matrix, int rows, int cols, int type) {
	for (int i = 0; i < rows; i++) {
		for (int j = 1; j < cols; j++) {
			int key = matrix[i][j];
			int k = j - 1;
			if (type == 1) {
				while (k >= 0 && matrix[i][k] > key) {
					matrix[i][k + 1] = matrix[i][k];
					k--;
				}
			}
			else if (type == 2) {
				while (k >= 0 && matrix[i][k] < key) {
					matrix[i][k + 1] = matrix[i][k];
					k--;
				}
			}
			matrix[i][k + 1] = key;
		}
	}
}

//Функция: сортировка Хоара (2)
void QuickSort(int**& matrix, int rows, int cols, int type) {
	for (int row = 0; row < rows; row++) {
		auto sort = [&](int left, int right, auto&& sort) -> void {
			if (left >= right) return;
			int pivot = matrix[row][(left + right) / 2];
			int i = left, j = right;
			while (i <= j) {
				if (type == 1) {
					while (matrix[row][i] < pivot) i++;
					while (matrix[row][j] > pivot) j--;
				}
				else if (type == 2) {
					while (matrix[row][i] > pivot) i++;
					while (matrix[row][j] < pivot) j--;
				}
				if (i <= j) {
					std::swap(matrix[row][i], matrix[row][j]);
					i++;
					j--;
				}
			}
			sort(left, j, sort);
			sort(i, right, sort);
			};
		sort(0, cols - 1, sort);
	}
}

//Функция: сортировка выбором (3)
void SelectionSort(int**& matrix, int rows, int cols, int type) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols - 1; j++) {
			int extreme_index = j;
			for (int k = j + 1; k < cols; k++) {
				if (type == 1) {
					if (matrix[i][k] < matrix[i][extreme_index]) {
						extreme_index = k;
					}
				}
				else if (type == 2) {
					if (matrix[i][k] > matrix[i][extreme_index]) {
						extreme_index = k;
					}
				}
			}
			if (extreme_index != j) {
				std::swap(matrix[i][j], matrix[i][extreme_index]);
			}
		}
	}
}

//Функция: сортировка пузырьком (4)
void BubbleSort(int**& matrix, int rows, int cols, int type) {
	if (type == 1) {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols - 1; j++) {
				for (int k = 0; k < cols - j - 1; k++) {
					if (matrix[i][k + 1] < matrix[i][k]) {
						std::swap(matrix[i][k], matrix[i][k + 1]);
					}
				}
			}
		}
	}
	else if (type == 2) {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols - 1; j++) {
				for (int k = 0; k < cols - j - 1; k++) {
					if (matrix[i][k + 1] > matrix[i][k]) {
						std::swap(matrix[i][k], matrix[i][k + 1]);
					}
				}
			}
		}
	}
}

//Функция: сортировка подсчетом (5)
void CountingSort(int**& matrix, int rows, int cols, int type) {
	for (int i = 0; i < rows; i++) {
		int min_val = matrix[i][0];
		int max_val = matrix[i][0];
		for (int j = 1; j < cols; j++) {
			if (matrix[i][j] < min_val) min_val = matrix[i][j];
			if (matrix[i][j] > max_val) max_val = matrix[i][j];
		}
		int range = max_val - min_val + 1;
		if (range <= 0) continue;
		int* count = new int[range]();
		for (int j = 0; j < cols; j++) {
			count[matrix[i][j] - min_val]++;
		}
		int index = 0;
		if (type == 1) {
			for (int j = 0; j < range; j++) {
				while (count[j] > 0) {
					matrix[i][index++] = j + min_val;
					count[j]--;
				}
			}
		}
		else if (type == 2) {
			for (int j = range - 1; j >= 0; j--) {
				while (count[j] > 0) {
					matrix[i][index++] = j + min_val;
					count[j]--;
				}
			}
		}
		delete[] count;
	}
}

//Функция: сортировка слиянием (6)
void MergeSort(int**& matrix, int rows, int cols, int type) {
	for (int i = 0; i < rows; i++) {
		auto mergeSortRow = [&](int row, int left, int right, auto&& self) -> void {
			if (left >= right) return;
			int mid = (left + right) / 2;
			self(row, left, mid, self);
			self(row, mid + 1, right, self);
			int* temp = new int[right - left + 1];
			int i = left, j = mid + 1, k = 0;
			while (i <= mid && j <= right) {
				if ((type == 1 && matrix[row][i] <= matrix[row][j]) ||
					(type == 2 && matrix[row][i] >= matrix[row][j])) {
					temp[k++] = matrix[row][i++];
				}
				else {
					temp[k++] = matrix[row][j++];
				}
			}
			while (i <= mid) temp[k++] = matrix[row][i++];
			while (j <= right) temp[k++] = matrix[row][j++];
			for (int idx = 0; idx < k; idx++) {
				matrix[row][left + idx] = temp[idx];
			}
			delete[] temp;
			};
		mergeSortRow(i, 0, cols - 1, mergeSortRow);
	}
}

int main()
{
	setlocale(LC_ALL, "RUS");
	int number, rows, cols;
	std::cout << "СОЗДАНИЕ МАТРИЦЫ\n\n";
	std::cout << "Введите число строк: ";
	std::cin >> rows;
	if (!IsCorrectInput() or rows < 1) {
		std::cout << "\nОшбика, попробуйте еще раз!\n";
		return 0;
	}
	std::cout << "Введите число столбцов: ";
	std::cin >> cols;
	if (!IsCorrectInput() or cols < 1) {
		std::cout << "\nОшбика, попробуйте еще раз!\n";
		return 0;
	}
	std::cout << "\n";
	std::cout << "Способы заполнения матрицы:\nДля заполнения матрицы вручную выберите 1.\nДля заполнения матрицы рандомайзером выберите 2.\nВыберите способ заполнения матрицы: ";
	std::cin >> number;
	std::cout << "\n";
	if (!IsCorrectInput() or number < 1 or number > 2) {
		std::cout << "\nОшбика, попробуйте еще раз!\n";
		return 0;
	}
	int** matrix = nullptr;
	MemoryAllocation(matrix, rows, cols);
	if (number == 1) {
		FillingManually(matrix, rows, cols);
	}
	if (number == 2) {
		int min, max;
		std::cout << "Введите минимальный элемент матрицы: ";
		std::cin >> min;
		if (!IsCorrectInput()) {
			std::cout << "\nОшбика, попробуйте еще раз!\n";
			return 0;
		}
		std::cout << "Введите максимальный элемент матрицы: ";
		std::cin >> max;
		if (!IsCorrectInput() or min > max) {
			std::cout << "\nОшбика, попробуйте еще раз!\n";
			return 0;
		}
		FillingRandomly(matrix, rows, cols, min, max);
	}
	PrintMatrix(matrix, rows, cols);
	int type, choice;
	std::cout << "СОРТИРОВКА МАТРИЦЫ\n\n";
	std::cout << "Виды сортировки матрицы:\nДля сортировки матрицы по возрастанию выберите 1\nДля сортировки матрицы по убыванию выберите 2\nВыберите вид сортировки матрицы: ";
	std::cin >> type;
	std::cout << "\n";
	if (!IsCorrectInput() or type < 1 or type > 2) {
		std::cout << "\nОшбика, попробуйте еще раз!\n";
		return 0;
	}
	std::cout << "Способы сортировки матрицы:\nДля сортировки вставками выберите 1.\nДля сортировки Хоара выберите 2.\nДля сортировки выбором выберите 3.\nДля сортировки пузырьком выберите 4.\nДля сортировки подсчетом выберите 5.\nДля сортировки слиянием выберите 6.\n\nВыберите способ сортировки матрицы: ";
	std::cin >> choice;
	if (!IsCorrectInput() or choice < 1 or choice > 6) {
		std::cout << "\nОшбика, попробуйте еще раз!\n";
		return 0;
	}
	//Сортировка вставками (1)
	if (choice == 1) {
		InsertionSort(matrix, rows, cols, type);
	}
	//Сортировка Хоара (2)
	if (choice == 2) {
		QuickSort(matrix, rows, cols, type);
	}
	//Сортировка выбором (3)
	if (choice == 3) {
		SelectionSort(matrix, rows, cols, type);
	}
	//Сортировка пузырьком (4)
	if (choice == 4) {
		BubbleSort(matrix, rows, cols, type);
	}
	//Сортировка подсчетом (5)
	if (choice == 5) {
		CountingSort(matrix, rows, cols, type);
	}
	//Сортировка слиянием (6)
	if (choice == 6) {
		MergeSort(matrix, rows, cols, type);
	}
	std::cout << "\nОтсортированная матрица: \n\n";
	PrintMatrix(matrix, rows, cols);
	MemoryDelete(matrix, rows);
	return 0;
}