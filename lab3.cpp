#include <iostream>

using namespace std;

int main() {
	int a,b,c,d;

	cout << "Enter B: ";
	cin >> b;

	cout << "Enter C: ";
	cin >> c;
	cout << endl;

	a = b + c;
	d = a << 1;

	cout << "A = (B + C): " << a << endl;
	cout << "D = (A << 1): " << d << endl;

return 0;
}