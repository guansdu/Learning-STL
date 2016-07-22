#include <iostream>
#include "my_list.h"

using namespace std;

int main()
{
	cout << "----init:" << endl;
	List<int> li;
	cout << "size:"<< li.size() << endl;    //0

	li.push_back(4);
	li.push_back(4);
	li.push_back(3);
	li.push_back(3);
	li.push_back(2);
	li.push_back(2);
	li.push_back(1);
	li.push_back(1);
	li.print();    //4 4 3 3 2 2 1 1
	cout << "size:"<< li.size() << ", front:"<<li.front() << ", back:" << li.back() << endl;
	
	cout << "----use push_front:" << endl;
	li.push_front(5);
	li.print();    //5 4 4 3 3 2 2 1 1
	cout << "size:"<< li.size() << ", front:"<<li.front() << ", back:" << li.back() << endl;

	cout << "----use unique:" << endl;
	li.unique();
	li.print();    //5 4 3 2 1
	cout << "size:"<< li.size() << ", front:"<<li.front() << ", back:" << li.back() << endl;

	cout << "----use remove:" << endl;
	li.remove(1);
	li.print();    //5 4 3 2
	cout << "size:"<< li.size() << ", front:"<<li.front() << ", back:" << li.back() << endl;

	cout << "----use pop_back:" << endl;
	li.pop_back();
	li.print();    //5 4 3
	cout << "size:"<< li.size() << ", front:"<<li.front() << ", back:" << li.back() << endl;

	cout << "----use pop_front:" << endl;
	li.pop_front();
	li.print();    //4 3
	cout << "size:"<< li.size() << ", front:"<<li.front() << ", back:" << li.back() << endl;
	
	getchar();
	return 0;
}
