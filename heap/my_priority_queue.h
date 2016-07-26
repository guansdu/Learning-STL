
#ifndef _MY_PRIORITY_QUEUE_H
#define _MY_PRIORITY_QUEUE_H 

#include "my_heap.h"

#include <vector>

using namespace std;

template <class T>
class MyPriorityQueue
{
public:
	MyPriorityQueue() : ve() { }

	MyPriorityQueue(T* first, const int n);

	~MyPriorityQueue();

	bool empty() const { return ve.empty(); }

	int size() const { return ve.size(); }

	T top() const { return ve.front(); }

	void push(const T& x);

	void pop();

private:
	vector<T> ve;
};

template <class T>
MyPriorityQueue<T>::MyPriorityQueue(T* first, const int n)
{
	for (int i = 0; i < n;i ++)
	{
		ve.push_back(*first);
		first++;
	}
	MakeHeap<T>(ve.begin(), ve.end());

}

template <class T>
MyPriorityQueue<T>::~MyPriorityQueue()
{

}

template <class T>
void MyPriorityQueue<T>::push(const T& x)
{
	ve.push_back(x);
	PushHeap<T>(ve.begin(), ve.end());
}

template <class T>
void MyPriorityQueue<T>::pop()
{
	PopHeap<T>(ve.begin(), ve.end());
	ve.pop_back();
}

#endif //_MY_PRIORITY_QUEUE_H 
