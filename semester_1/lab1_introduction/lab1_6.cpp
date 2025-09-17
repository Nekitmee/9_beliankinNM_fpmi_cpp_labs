#include <iostream>

int main()
{
    setlocale(LC_ALL, "RUS");
    int n;
    int summ = 0;
    std::cout << "Введите переменную n:  \n";
    std::cin >> n;
    std::cout << "\n";
    if (n <= 0) {
        std::cout << "Ошибка 404, проверьте правильность ввода: \nn > 0\n";
        return 404;
    }
    else {
        while (n != 0) {
            for (int i = 1; n != 0;) {
                summ += i;
                i += 2;
                n -= 1;
            }
            std::cout << "Ответ: " << summ;
        }
    }
    return 0;
}
