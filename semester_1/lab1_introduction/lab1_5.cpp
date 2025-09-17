#include <iostream>

int main()
{
    setlocale(LC_ALL, "RUS");
    int n, m, x;
    std::cout << "Введите числа n и m: \n";
    std::cin >> n >> m;
    if (n <= 0 || m <= 0) {
        std::cout << "Ошибка 404, роверьте правильность ввода: \nn > 0 \nm > 0";
        return 404;
    }
    else {
        if (n > m) {
            x = n;
        }
        else {
            x = m;
        }
        std::cout << "Ответ: \n";
        for (int i = 1; i < x;) {
            if (n % i == 0 and m % i == 0) {
                std::cout << i << " ";
            }
            i++;
        }
    }
    return 0;
}
