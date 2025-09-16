#include <iostream>

int main()
{
    setlocale(LC_ALL, "RUS");
    int a, b, d;
    std::cout << "Введите переменные А, B, D: \n";
    std::cin >> a;
    std::cin >> b;
    std::cin >> d;
    if (a > b || d < 0) {
        std::cout << "Ошибка 404, проверьте правильнность ввода:\nb > a\nd > 0";
        return 404;
    }
    else {
        for (int i=a; i < b;i+=d) {
            if (i % 3 == 0) {
                std::cout << i << "\n";
            }
        }
        return 0;
    }
}
