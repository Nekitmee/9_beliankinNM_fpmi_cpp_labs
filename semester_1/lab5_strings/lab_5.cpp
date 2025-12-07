#include <iostream>
#include <string>

void EnterString(std::string& str);
void CheckString(std::string str);
void UpToDown(std::string& str);
bool IsPalindrome(std::string str);
void PunctuationToSpaces(std::string& str);
void FindPalindromes(std::string& str);
void FindLongestPalindrome(std::string& str);
void Print(std::string str);

int main() {
    setlocale(LC_ALL, "RUS");
    try {
        std::string str;
        EnterString(str);
        CheckString(str);
        UpToDown(str);
        PunctuationToSpaces(str);
        FindPalindromes(str);
        FindLongestPalindrome(str);
        Print(str);
        return 0;
    }
    catch (const char* msg) {
        std::cout << msg << std::endl;
        return 1;
    }
}

//Функция: Ввод строки
void EnterString(std::string& str) {
    std::cout << "\t\t\t\t ВВОД СТРОКИ\nПравила ввода:\n1) Нельзя вводить русские буквы\n2) Слова должны быть разделены только символами (,.;)\n3) Нельзя вводить пробелы\n4) После последнего слова не должно стоять ничего\n5) Нельзя вводить цифры\n6) Нельзя вставлять между словами 2 и более разделительных знаков\nВведите вашу строку: ";
    std::getline(std::cin, str);
    std::cout << std::endl;
}

//Функция: Полная проверка строки на исключения
void CheckString(std::string str) {
    std::string legal_symbols = ".,;";
    std::string russian_letters = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнопрстуфхцчшщъыьэюя";
    std::string english_letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::string symbols = "!@#$%^&*()_+~`\"№?_+/|}{][><";
    std::string numbers = "0123456789";
    //Проверка на пустую строку
    if (str.empty()) {
        throw "ОШИБКА! Строка пустая";
    }
    //Проверка на русские буквы
    if (str.find_first_of(russian_letters) != std::string::npos) {
        throw "ОШИБКА! В строке найдены русские буквы!";
    }
    //Проверка на пробелы
    if (str.find_first_of(' ') != std::string::npos) {
        throw "ОШИБКА! В строке найдены пробелы!";
    }
    //Проверка на последний символ
    char last_char = str.back();
    if (english_letters.find(last_char) == std::string::npos) {
        throw "ОШИБКА! В конце строки найден символ!";
    }
    //Проверка на неизвестные символы
    if (str.find_first_of(symbols) != std::string::npos) {
        throw "ОШИБКА! В строке найдены неизвестные символы!";
    }
    //Проверка на цифры
    if (str.find_first_of(numbers) != std::string::npos) {
        throw "ОШИБКА! В строке найдены цифры!";
    }
    //Проверка на несколько знаков подряд
    for (int i = 0; i < str.size() - 1; i++) {
        if (legal_symbols.find(str[i]) != std::string::npos && legal_symbols.find(str[i + 1]) != std::string::npos) {
            throw "ОШИБКА! В строке найдены два или более знака препинания подряд";
        }
    }
}

//Функция: Преобразование всех заглавных букв в строчные
void UpToDown(std::string& str) {
    for (int i = 0; i < str.size(); i++) {
        if (std::isupper(str[i])) {
            str[i] = std::tolower(str[i]);
        }
    }
}

//Функция: Поиск палиндрома 
bool IsPalindrome(std::string str) {
    size_t num = 0;
    for (int i = 0; i < str.size() / 2; i++) {
        if (str[i] != str[str.size() - 1 - i]) {
            num++;
        }
    }
    if (num == 0) {
        return true;
    }
    else {
        return false;
    }
}

//Функция: Замена всех знаков пробелами
void PunctuationToSpaces(std::string& str) {
    std::string punctuation = ".,;";
    while (str.find_first_of(punctuation) != std::string::npos) {
        str[str.find_first_of(punctuation)] = ' ';
    }
}

//Функция: Поиск всех слов-палиндромов
void FindPalindromes(std::string& str) {
    std::string new_str;
    size_t start = 0;
    size_t end = 0;
    while (start < str.length()) {
        start = str.find_first_not_of(' ', end);
        end = str.find(' ', start);
        if (end == std::string::npos) {
            end = str.length();
        }
        std::string word = str.substr(start, end - start);
        if (IsPalindrome(word)) {
            if (!new_str.empty()) {
                new_str += ',';
            }
            new_str += word;
        }
        start = end + 1;
    }
    str = new_str;
}

//Функция: Поиск самых длинных слов-палиндромов
void FindLongestPalindrome(std::string& str) {
    str += ',';
    std::string new_str;
    std::string current_word;
    size_t max_length = 0;
    for (size_t i = 0; i < str.length(); i++) {
        if (str[i] == ',') {
            if (!current_word.empty()) {
                if (current_word.length() > max_length) {
                    max_length = current_word.length();
                }
                current_word.clear();
            }
        }
        else {
            current_word += str[i];
        }
    }
    current_word.clear();
    bool first_word = true;
    for (size_t i = 0; i < str.length(); i++) {
        if (str[i] == ',') {
            if (!current_word.empty() && current_word.length() == max_length) {
                if (!first_word) {
                    new_str += ',';
                }
                new_str += current_word;
                first_word = false;
            }
            current_word.clear();
        }
        else {
            current_word += str[i];
        }
    }
    str.pop_back();
    str = new_str;
}

//Функция: Вывод строки
void Print(std::string str) {
    std::cout << str << "\n";
}