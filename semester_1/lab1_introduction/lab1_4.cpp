#include <iostream>

int main()
{
    setlocale(LC_ALL, "RUS");
    int k;
    int ans = 1;
    std::cout << "Введите переменную k: \n";
    std::cin >> k;
    std::cout << "\n";
    if (k < 0) {
        std::cout << "Ошибка 404, проверьте правильность ввода:\nk >= 0\n";
        return 404;
    }
    if (k == 0) {
        std::cout << "Ответ: 1\n";
    }
    if (k > 0 and k % 2 == 0) {
        for (int i = 2; i <= k;) {
            ans *= i;
            i += 2;
        }
        std::cout << "Ответ: " << ans;
    }
    else {
        for (int i = 1; i <= k;) {
            ans *= i;
            i += 2;
        }
        std::cout << "Ответ: " << ans;
    }
    return 0;
}
