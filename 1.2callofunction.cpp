#include <iostream>
void swap(int &a, int &b) {
	int tmp = a;
	a = b;
	b = tmp;
}
void sortAscending(int &a, int &b, int &c) {
	if (a > b) swap(a, b);
	if (a > c) swap(a, c);
	if (b > c) swap(b, c);
}

int main() {
	//input three numbers
	int num1, num2, num3;
	std::cout << "Enter three integers: ";
	std::cin >> num1 >> num2 >> num3;

	sortAscending(num1, num2, num3);

    std::cout << "Sorted in ascending order: " << num1 << " " << num2 << " " << num3 << std::endl;

    return 0;
}
