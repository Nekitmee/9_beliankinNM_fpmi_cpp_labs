#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

bool isPalindrome(const std::string& s);
int maxPalindromeLength(const std::string& str);

int main() {
    try {
        setlocale(LC_ALL, "Ru");
        std::ifstream inputFile("input.txt");
        if (!inputFile.is_open()) {
            throw "Не удалось открыть файл input.txt";
        }

        std::vector<std::pair<std::string, int>> allLines;
        std::string line;
        int globalMaxLength = 0;

        while (std::getline(inputFile, line)) {
            int maxLen = maxPalindromeLength(line);
            allLines.push_back({ line, maxLen });

            if (maxLen > globalMaxLength) {
                globalMaxLength = maxLen;
            }
        }

        inputFile.close();

        std::cout << "Максимальная длина палиндрома в файле: " << globalMaxLength << std::endl;
        std::cout << "\nСтроки с максимальным палиндромом (первые 10):\n" << std::endl;

        int count = 0;
        for (const auto& item : allLines) {
            if (item.second == globalMaxLength) {
                if (count >= 10) break;

                std::cout << "[" << count + 1 << "] Длина палиндрома: " << item.second << std::endl;
                std::cout << "Текст: " << item.first << std::endl;
                std::cout << std::endl;
                count++;
            }
        }

        if (count == 0) {
            std::cout << "Файл пуст или не содержит строк с палиндромами" << std::endl;
        }

        return 0;
    }
    catch (const char* msg) {
        std::cout << msg << "\n";
        return 1;
    }
}

//Функция: Проверка строки на палиндром
bool isPalindrome(const std::string& s) {
    int left = 0;
    int right = s.length() - 1;

    while (left < right) {
        if (s[left] != s[right]) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}

//Функция: поиск самого длинного палиндрома
int maxPalindromeLength(const std::string& str) {
    int maxLen = 1;
    int n = str.length();

    for (int i = 0; i < n; i++) {
        for (int j = i + maxLen; j < n; j++) {
            int len = j - i + 1;

            bool isPal = true;
            for (int k = 0; k < len / 2; k++) {
                if (str[i + k] != str[j - k]) {
                    isPal = false;
                    break;
                }
            }
            if (isPal && len > maxLen) {
                maxLen = len;
            }
        }
    }

    return maxLen;
}