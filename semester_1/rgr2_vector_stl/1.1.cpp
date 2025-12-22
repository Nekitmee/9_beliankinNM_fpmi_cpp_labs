#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <limits>

void part1() {
    std::cout << "Часть 1.1" << std::endl;
    std::cout << "Введите целые числа (для завершения ввода введите любой нечисловой символ):" << std::endl;

    std::vector<int> vec;
    int num;

    try {
        while (std::cin >> num) {
            vec.push_back(num);
        }

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (vec.empty()) {
            throw "Вектор пуст!";
        }

        std::cout << "\nИсходный вектор: ";
        for (int el : vec) std::cout << el << " ";
        std::cout << std::endl;

        int sum = 0;
        for (int el : vec) sum += el;
        std::cout << "1. Сумма чисел: " << sum << std::endl;

        std::cout << "2. Общее количество чисел: " << vec.size() << std::endl;

        int target;
        std::cout << "Введите число для поиска: ";
        if (!(std::cin >> target)) throw "Ошибка ввода числа!";
        int count_target = 0;
        for (int el : vec) if (el == target) count_target++;
        std::cout << "3. Количество чисел, равных " << target << ": " << count_target << std::endl;

        int n;
        std::cout << "Введите число n для условия 'больше чем n': ";
        if (!(std::cin >> n)) throw "Ошибка ввода числа!";
        int count_greater = 0;
        for (int el : vec) if (el > n) count_greater++;
        std::cout << "4. Количество чисел, больших чем " << n << ": " << count_greater << std::endl;

        int average = sum / vec.size();
        for (int& el : vec) if (el == 0) el = average;
        std::cout << "5. После замены нулей средним арифметическим (" << average << "): ";
        for (int el : vec) std::cout << el << " ";
        std::cout << std::endl;

        int start_idx, end_idx;
        std::cout << "Введите начальный индекс интервала: ";
        if (!(std::cin >> start_idx)) throw "Ошибка ввода индекса!";
        std::cout << "Введите конечный индекс интервала: ";
        if (!(std::cin >> end_idx)) throw "Ошибка ввода индекса!";

        if (start_idx < 0 || start_idx >= vec.size() ||
            end_idx < 0 || end_idx >= vec.size() || start_idx > end_idx) {
            throw "Неверные индексы интервала!";
        }

        int interval_sum = 0;
        for (int i = start_idx; i <= end_idx; ++i) {
            interval_sum += vec[i];
        }

        for (int& el : vec) {
            el += interval_sum;
        }
        std::cout << "6. После добавления суммы интервала [" << start_idx
            << "," << end_idx << "] = " << interval_sum << ": ";
        for (int el : vec) std::cout << el << " ";
        std::cout << std::endl;

        int max_elem = vec[0];
        int min_elem = vec[0];
        for (int el : vec) {
            if (el > max_elem) max_elem = el;
            if (el < min_elem) min_elem = el;
        }
        int diff = max_elem - min_elem;

        for (int& el : vec) {
            if (std::abs(el) % 2 == 0) el = diff;
        }
        std::cout << "7. После замены чисел с четным модулем на разность ("
            << diff << "): ";
        for (int el : vec) std::cout << el << " ";
        std::cout << std::endl;

        std::vector<int> result;
        std::vector<bool> used(1000000, false);

        for (int el : vec) {
            int abs_val = std::abs(el);
            if (!used[abs_val]) {
                result.push_back(el);
                used[abs_val] = true;
            }
        }

        vec = result;
        std::cout << "8. После удаления равных по модулю чисел (оставлено первое): ";
        for (int el : vec) std::cout << el << " ";
        std::cout << std::endl;

    }
    catch (const char* error_msg) {
        std::cout << "Ошибка: " << error_msg << std::endl;
    }
}