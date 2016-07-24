#include <iostream>
#include "my_slist.h"
//author: Klaus
//time: 2016.7.24

using namespace std;

int main()
{
	Slist<int> sli;
	cout << "size:" <<sli.size() << ", is empty:"<<sli.empty() << endl;

	cout << "do push:" << endl;
	sli.push_front(1);
	sli.push_front(2);
	sli.push_front(3);

	sli.print();

	cout << "size:" <<sli.size() << ", is empty:"<<sli.empty() << endl;
	cout << "get front:" <<sli.front() << endl;

	cout << "do pop:" << endl;
	sli.pop_front();
	cout << "size:" <<sli.size() << ", is empty:"<<sli.empty() << endl;
	cout << "get front:" <<sli.front() << endl;
	
	sli.print();

	system("pause");
	return 0;
}
