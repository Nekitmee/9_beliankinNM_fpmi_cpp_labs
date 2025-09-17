#include <iostream>

int main()
{
    setlocale(LC_ALL, "RUS");
    int n;
    int summ = 0;
    std::cout << "Введите число n: ";
    std::cin >> n;
    if (n <= 1) {
        std::cout << "Ошибка 404, проверьте правильность ввода: \nn > 1";
        return 404;
    }
    else {
        for (int i = 1; i <= n;) {
            summ += std::pow(i, i);
            i++;
        }
        std::cout << "Сумма равна: " << summ << "\n\n";
    }
    int a, b;
    long long d;
    a = std::pow(5, 5);
    b = std::pow(6, 6);
    d = std::pow(10, 10);
    std::cout << "Сумма для n = (5, 6, 10) = ";
    std::cout << a << " " << b << " " << d << "\n\n";
    long long z, x, c, v;
    z = std::pow(100, 100);
    x = std::pow(200, 200);
    c = std::pow(500, 500);
    v = std::pow(1000, 1000);
    std::cout << "Сумма для n = (100, 200, 500, 1000) = "; //Такое происходит из-за переполнения переменной типа long long
    std::cout << z << " " << x << " " << c << " " << v;    //Которая может вместить числа от -9 223 372 036 854 775 808 до 9 223 372 036 854 775 807
    return 0;
}
