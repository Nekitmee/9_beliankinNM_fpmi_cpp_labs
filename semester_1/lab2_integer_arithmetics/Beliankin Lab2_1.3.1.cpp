/*Нужно ввести число -2147483648 так как для типа int абсолютные показатели
наибольшего и наименьшего возможного значения будут отличаться на единицу
(минимальное - 2147483648, максимальное 2147483647), из-за этого функция
abs() не сможет найти такое же положительное число и примет значение -2147483648,
а дальше функция IsNotNegative() примет значение true, а функция std_non_negative_check()
false и вылезет сообщение "Shit, you broke my program :("*/

#include <iostream>
void TryRead(int& number) {
	if (!(std::cin >> number)) {
		std::cout << "Fail on reading the number." << std::endl;
		exit(0);
	}
}
bool IsNotNegative(int number) {
	return abs(number) == number;
}
int main() {
	int number;
	std::cout << "Enter the number: ";
	TryRead(number);
	bool std_non_negative_check = (number >= 0);
	if (IsNotNegative(number) == std_non_negative_check) {
		std::cout << "Try again...." << std::endl;
	}
	else {
		std::cout << "Shit, you broke my program :(" << std::endl;
		exit(1);
	}
	return 0;
}