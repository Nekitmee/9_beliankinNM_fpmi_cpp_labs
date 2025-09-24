/*Нужно ввести в одну из переменных число = (2^32)/n ,а во вторую переменную
ввести число n, где n - это число, такое, что (2^32)%n == 0. После чего вылезет надпись
"Shit, you broke my program :(" Это как и в первой программе происходит из-за переполнения
типа Int*/

#include <iostream>
#include <numeric>
int Gcd(int a, int b) {
	while (a * b) {
		int rem = a % b;
		a = b;
		b = rem;
	}
	return std::max(a, b);
}
void TryRead(int& number) {
	if (!(std::cin >> number)) {
		std::cout << "Fail on reading the number" << std::endl;
		exit(0);
	}
}
int main() {
	int a, b;
	std::cout << "Enter a: ";
	TryRead(a);
	std::cout << "Enter b: ";
	TryRead(b);
	if (a <= 0 || b <= 0) {
		std::cout << "Numbers should be positive" << std::endl;
		return 0;
	}
	int gcd1 = Gcd(a, b);
	int gcd2 = std::gcd(a, b);
	if (gcd1 != gcd2) {
		std::cout << "Shit, you broke my program :(" << std::endl;
		return 1;
	}
	else {
		std::cout << "Try again..." << std::endl;
	}
	return 0;
}