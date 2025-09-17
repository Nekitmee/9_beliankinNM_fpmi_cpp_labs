#include <iostream>

int main()
{
    setlocale(LC_ALL, "RUS");
    int n;
    int summ = 0;
    int mult = 1;
    std::cout << "Введите переменную n:\n";
    std::cin >> n;
    if (n <= 1) {
        std::cout << "Ошибка 404, проверьте условие: \nn > 1";
        return 404;
    }
    else {
        for (int i = 0; i <= n;) {
            summ += i;
            i+=2;
        }
        for (int l = 1; l <= n;) {
            mult *= l;
            l += 2;
        }
        std::cout << summ << "\n";
        std::cout << mult << "\n";
        return 0;
    }
}