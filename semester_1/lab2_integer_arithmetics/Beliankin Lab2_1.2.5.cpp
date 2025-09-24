#include <iostream>

//Функция: Проверка числа на натуральность 
bool natural(int num1) {
    if (num1 < 1) {
        std::cout << "Ошибка! Число должно быть натуральным.\n";
        return false;
    }
    else {
        return true;
    }
}

//Функция: Проверка числа на палиндром
bool palindrome(int num2) {
    int original = num2;
    int rev = 0;
    while (num2 > 0) {
        rev = rev * 10 + num2 % 10;
        num2 /= 10;
    }
    return (original == rev);
}

int main()
{
    setlocale(LC_ALL, "RUS");
    int n;
    std::cout << "Введите натуральное число: ";

    //Проверка ввода числа
    if (!(std::cin >> n)) {
        std::cout << "Ошибка: введено не число.\n";
        return 1;
    }
    //Проверка числа на натуральность 
    if (!natural(n)) {
        return 1;
    }
    //Проверка числа и его квадрата на палиндром
    if (palindrome(n) && palindrome(n * n)) {
        std::cout << "Ваше число является двойным палиндромом!\n";
    }
    else {
        std::cout << "Ваше число не является двойным палиндромом.\n";
    }
    return 0;
}