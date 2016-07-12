#include <iostream>
#include "learn-stl.h"
using namespace std;

int Max(int x, int y)
{
	return (x > y) ? x : y;
}

template <class T>
T MaxT(T x, T y)
{
	return (x > y) ? x : y;
}

int main()
{	
	CalcT<int> calc;
	cout << calc.DoAdd(2,3) << endl;
	CalcT<double> calc1;
	cout << calc1.DoMulitply(1.2, 1.2) << endl;
	
	cout << Max(2, 3) << endl;

	cout << MaxT(1.2, 2.2) << endl;
	cout << MaxT(1, 2) << endl;
	cout << MaxT('a', 'b') << endl;

	cout << MaxT<int>(3, 4) << endl;
	return 0;
}
