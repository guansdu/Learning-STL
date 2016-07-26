#include "my_priority_queue.h"

#include <iostream>
#include <vector>
#include "my_heap.h"
#include "my_priority_queue.h"

using namespace std;

int main()
{
	//----
	//Heap
	//----
	int ia[9] = {0,1,2,3,4,8,9,3,5};
	vector<int> ve(ia, ia+9);
	MakeHeap<int> (ve.begin(), ve.end());

	for (int i = 0; i < ve.size(); i++)
		cout << ve[i] << " ";    //9  5 8 3 4 0 2 3 1
	cout << endl;

	ve.push_back(7);
	PushHeap<int>(ve.begin(), ve.end());

	for (int i = 0; i < ve.size(); i++)
		cout << ve[i] << " ";    //9 7 8 3 5 0 2 3 1 4
	cout << endl;

	PopHeap<int> (ve.begin(), ve.end());
	for (int i = 0; i < ve.size(); i++)
		cout << ve[i] << " ";    //8 7 4 3 5 0 2 3 1 9
	cout << endl;

	ve.pop_back();    //remove 9
	SortHeap<int>(ve.begin(), ve.end());
	for (int i = 0; i < ve.size(); i++)
		cout << ve[i] << " ";    //0 1 2 3 3 4 5 7 8 
	cout << endl;
	
	//----
	//Priority Queue
	//----	
	int ar[9] = {0, 1, 3, 5, 2, 4 ,8 ,6 ,7};
	MyPriorityQueue<int> mpq(ar, 9);
	cout << mpq.size() << endl;    //9
	
	cout << mpq.top() << endl;    //8

	while (!mpq.empty())
	{
		cout << mpq.top() << " ";    //8 7 6 5 4 3 2 1 0
		mpq.pop();
	}
	cout << endl;
	getchar();
	return 0;
}
