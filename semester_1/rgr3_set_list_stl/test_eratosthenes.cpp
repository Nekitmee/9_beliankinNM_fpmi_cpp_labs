#include <iostream>
#include <set>
#include <cassert>
#include "eratosthenes.cpp"

void test_eratosthenes() {
    std::set<int> result;

    result = eratosthenes_sieve(1);
    assert(result.empty());
    std::cout << "Тест 1 пройден: N=1" << std::endl;

    result = eratosthenes_sieve(2);
    assert(result.size() == 1);
    assert(*result.begin() == 2);
    std::cout << "Тест 2 пройден: N=2" << std::endl;

    result = eratosthenes_sieve(10);
    std::set<int> expected = { 2, 3, 5, 7 };
    assert(result == expected);
    std::cout << "Тест 3 пройден: N=10" << std::endl;

    result = eratosthenes_sieve(20);
    std::set<int> expected2 = { 2, 3, 5, 7, 11, 13, 17, 19 };
    assert(result == expected2);
    std::cout << "Тест 4 пройден: N=20" << std::endl;

    result = eratosthenes_sieve(30);
    std::set<int> expected3 = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };
    assert(result == expected3);
    std::cout << "Тест 5 пройден: N=30" << std::endl;

    std::cout << "Все тесты пройдены успешно!" << std::endl;
}

int main() {
    test_eratosthenes();
    return 0;
}