#include <iostream>

int main()
{
    setlocale(LC_ALL, "RUS");
    int n, N, a, A, rev =0, REV =0;
    bool x, X;
    std::cout << "Введите ваше число: \n";
    std::cin >> n;
    if (n < 1) {
        std::cout << "Ошибка 404. Ваше число должно быть больше 0. Попробуйте еще раз.";
        return 404;
    }
    else {
        N = n * n;

        a = n;
        while (a > 0) {
            rev = (rev * 10) + a % 10;
            a /= 10;
        }
        if (rev == n) {
            x = true;
        }
        else {
            x = false;
        }
        A = N;
        while (A > 0) {
            REV = (REV * 10) + A % 10;
            A /= 10;
        }
        if (REV == N) {
            X = true;
        }
        else {
            X = false;
        }
        if (x == true and X == true) {
            std::cout << "Ваше число является двойным палиндромом!";
        }
        else {
            std::cout << "Ваще число не является двойным палиндромом!";
        }
    }
}