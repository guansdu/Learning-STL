#include <iostream>
#include <string>

template <class T> struct MyIter
{
	typedef T value_type;
	T* ptr;
	MyIter(T* p = 0) : ptr(p) { }
	T& operator*() const {return *ptr;}
	//...
};

template <class I>
struct iterator_traits
{
	typedef typename I::value_type value_type;
};

//template partial specialization

template <class T>
struct iterator_traits<T*>    //native pointer
{
	typedef T value_type;
};

template <class T>
struct iterator_traits<const T*>    //pointer to const
{
	typedef T value_type;
};

template <class I>
typename iterator_traits<I>::value_type    //the return type of Func
Func(I iter)
{
	return *iter;
}

int main()
{
	int a = 7;
	int* pt  = &a;
	std::cout << Func(pt) << std::endl;    //output:7

	MyIter<int> iter(new int(8));
	std::cout << Func(iter) << std::endl;    //output:8

	getchar();
	return 0;
}
