#include <iostream>
#include <string>
#include <vector>
#include <cctype>

bool IsPolindrome(std::vector<char> word);
void FillingString(std::string& str);
void CapitalLettersToLowercase(std::string& str);
void CheckSpaces(const std::string& str);
void ReplacingPunctuationMarksWithCommas(std::string& str);
void PrintStr(const std::string& str);
void CheckRepeatingPunctuation(const std::string& str);
void CheckUnknownCharacters(const std::string& str);
void FindLongestPalindromes(const std::string& str);

int main() {
    setlocale(LC_ALL, "RUS");
    try {
        std::string str;
        FillingString(str);
        CheckSpaces(str);
        CheckUnknownCharacters(str);
        CapitalLettersToLowercase(str);
        ReplacingPunctuationMarksWithCommas(str);
        CheckRepeatingPunctuation(str);
        PrintStr(str);
        FindLongestPalindromes(str);
        return 0;
    }
    catch (const char* msg) {
        std::cout << msg << std::endl;
        return 1;
    }
}

bool IsPolindrome(std::vector<char> word) {
    for (size_t i = 0; i < word.size() / 2; i++) {
        if (word[i] != word[word.size() - i - 1]) {
            return false;
        }
    }
    return true;
}

void FillingString(std::string& str) {
    std::cout << "Введите слова, разделенные знаками препинания {. , ; :}: ";
    std::getline(std::cin, str);
}

void CapitalLettersToLowercase(std::string& str) {
    for (size_t i = 0; i < str.size(); i++) {
        str[i] = std::tolower(static_cast<unsigned char>(str[i]));
    }
}

void CheckSpaces(const std::string& str) {
    if (str.find(' ') != std::string::npos) {
        throw "ОШИБКА: в строке есть пробелы.";
    }
}

void ReplacingPunctuationMarksWithCommas(std::string& str) {
    std::string punctuation = ".:;";
    for (size_t i = 0; i < str.size(); i++) {
        if (punctuation.find(str[i]) != std::string::npos) {
            str[i] = ',';
        }
    }
}

void PrintStr(const std::string& str) {
    std::cout << "Вывод строки: " << str << std::endl;
}

void CheckRepeatingPunctuation(const std::string& str) {
    for (size_t i = 0; i < str.size() - 1; i++) {
        if (str[i] == ',' && str[i + 1] == ',') {
            throw "ОШИБКА: В строке повторяются знаки препинания.";
        }
    }
}

void CheckUnknownCharacters(const std::string& str) {
    std::string allowed_chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ,.;:";
    for (size_t i = 0; i < str.length(); i++) {
        if (allowed_chars.find(str[i]) == std::string::npos) {
            throw "ОШИБКА: В строке неизвестные символы.";
        }
    }
}

void FindLongestPalindromes(const std::string& str) {
    std::vector<std::string> all_palindromes;
    std::vector<std::string> longest_palindromes;
    size_t max_length = 0;

    size_t start_pos = 0;
    size_t comma_index = str.find(',', start_pos);
    if (comma_index == std::string::npos) {
        std::string single_word = str;
        if (!single_word.empty()) {
            std::vector<char> word_chars(single_word.begin(), single_word.end());
            if (IsPolindrome(word_chars)) {
                all_palindromes.push_back(single_word);
                max_length = single_word.length();
            }
        }
    }
    else {
        while (comma_index != std::string::npos) {
            std::string word = str.substr(start_pos, comma_index - start_pos);
            if (!word.empty()) {
                std::vector<char> word_chars(word.begin(), word.end());
                if (IsPolindrome(word_chars)) {
                    all_palindromes.push_back(word);
                    if (word.length() > max_length) {
                        max_length = word.length();
                    }
                }
            }
            start_pos = comma_index + 1;
            comma_index = str.find(',', start_pos);
        }
        if (start_pos < str.length()) {
            std::string last_word = str.substr(start_pos);
            if (!last_word.empty()) {
                std::vector<char> word_chars(last_word.begin(), last_word.end());
                if (IsPolindrome(word_chars)) {
                    all_palindromes.push_back(last_word);
                    if (last_word.length() > max_length) {
                        max_length = last_word.length();
                    }
                }
            }
        }
    }
    for (const auto& palindrome : all_palindromes) {
        if (palindrome.length() == max_length) {
            longest_palindromes.push_back(palindrome);
        }
    }
    if (longest_palindromes.empty()) {
        std::cout << "В строке не найдено слов-палиндромов." << std::endl;
    }
    else {
        std::string result;
        for (size_t i = 0; i < longest_palindromes.size(); i++) {
            result += longest_palindromes[i];
            if (i < longest_palindromes.size() - 1) {
                result += ",";
            }
        }
        std::cout << "Самые длинные слова-палиндромы: " << result << std::endl;
    }
    std::cout << std::endl;
}