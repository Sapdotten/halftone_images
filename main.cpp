#include <iostream>
using namespace std;

int main()
{
	short a = 10;
	a *= 1000000;
	cout << typeid(a).name() << a  << endl;
	return 0;
}
