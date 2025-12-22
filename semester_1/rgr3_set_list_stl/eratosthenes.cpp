#include <iostream>
#include <set>
#include <cmath>

std::set<int> eratosthenes_sieve(int n) {
    if (n < 2) {
        return {};
    }

    std::set<int> primes;
    for (int i = 2; i <= n; ++i) {
        primes.insert(i);
    }

    for (int p = 2; p * p <= n; ++p) {
        if (primes.find(p) != primes.end()) {
            for (int multiple = p * p; multiple <= n; multiple += p) {
                primes.erase(multiple);
            }
        }
    }

    return primes;
}

void print_primes(const std::set<int>& primes) {
    for (int prime : primes) {
        std::cout << prime << " ";
    }
    std::cout << std::endl;
}

int main() {
    int N;
    std::cout << "Введите N: ";
    std::cin >> N;

    std::set<int> primes = eratosthenes_sieve(N);

    std::cout << "Простые числа до " << N << ":\n";
    print_primes(primes);
    std::cout << "Количество простых чисел: " << primes.size() << std::endl;

    return 0;
}