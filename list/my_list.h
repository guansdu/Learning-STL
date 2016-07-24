#ifndef _MY_LIST_H
#define  _MY_LIST_H

#include <stdlib.h>
#include <cstddef>

using namespace std;

//list节点
template <class T>
struct ListNode 
{
	typedef void* void_pointer;
	void_pointer prev;
	void_pointer next;
	T data;
};

//list的迭代器
template <class T, class Ref, class Ptr>
struct ListIterator
{
	typedef ListIterator<T, T&, T*> iter;
	typedef ListIterator<T, Ref, Ptr> self;

	typedef Ref reference;
	typedef Ptr pointer;
	typedef ListNode<T>* link_type;
	link_type node;
	//构造函数
	ListIterator() { }
	ListIterator(link_type x) : node(x) { }    //！！（错：这里利用了ListNode默认的拷贝构造函数）这是初始化类的成员变量的方式，并不是拷贝构造函数
	ListIterator(const iter& x) : node(x.node) { }
	//操作符重载
	bool operator==(const self& x) { return node == x.node; }
	bool operator!=(const self& x) { return node != x.node; }

	reference operator*() const { return ((*node).data); }
	pointer operator->() const { return &(operator*()); }

	self& operator++()
	{
		node = (link_type) ((*node).next);
		return *this;
	}

	self& operator--()
	{
		node = (link_type) ((*node).prev);
		return *this;
	}
};

template <class T>
class List
{
public: 
	typedef ListIterator<T, T&, T*> iter;
protected:
	typedef ListNode<T> list_node;
public:
	typedef list_node* link_type;
protected:
	link_type node;

public:
	List()
	{
		node = (link_type)malloc(sizeof(struct ListNode<T>));
		node->next = node;
		node->prev = node;
	}
	//这里在返回节点时不可照搬书中代码，因为返回的node的类型是link_type，并不是iter。
	iter begin() { return iter( (link_type) ((*node).next) ); }
	iter end() { return iter(node); }

	//取首节点的元素值
	T& front() { return *begin(); }
	//取尾节点的元素值
	T& back() { return *(--end()); }

	bool empty() { return node->next == node; }
	//返回当前list中元素的个数
	size_t size()
	{
		size_t result = 0;
		iter first = begin();
		iter last = end();
		
		while (first != last)
		{
			++first;
			result++;
		}
		return result;
	}
	//在迭代器position之前插入一个值为x的节点
	iter insert(iter position, const T& x)
	{
		link_type tmp = (link_type)malloc(sizeof(struct ListNode<T>));
		tmp->data = x;

		tmp->next = position.node;
		tmp->prev = position.node->prev;
		(link_type(position.node->prev))->next = tmp;
		position.node->prev = tmp;

		return iter(tmp);
	}
	//插入一个节点，作为尾结点
	void push_back(const T& x)
	{
		insert(end(), x);
	}
	//插入一个结点，作为首节点
	void push_front(const T& x)
	{
		insert(begin(), x);
	}
	//删除position所指向的结点
	iter erase(iter position)
	{
		link_type next_node = link_type (position.node->next);
		link_type prev_node = link_type (position.node->prev);

		prev_node->next = next_node;
		next_node->prev = prev_node;

		free(position.node);

		return iter(next_node);
	}

	void pop_back()
	{
		iter tmp = end();
		erase(--tmp);	
	}
	void pop_front()
	{
		erase(begin());
	}
	//移除值为x的节点
	void remove(const T& x)
	{
		iter first = begin();
		iter last = end();

		while (first != last)
		{
			iter tmp = first;
			++first;
			if (*tmp == x)
				erase(tmp);
		}
	}
	//移除连续相同的元素
	void unique()
	{
		iter first = begin();
		iter last = end();
		if (first == last)
			return ;
		iter tmp = first;
		while (++first != last)
		{
			if (*tmp == *first)
			{
				erase(tmp);
			}
			tmp = first;
		}
	}
	//遍历并打印list
	void print()
	{
		iter tmp = begin();
		cout << "list: ";
		while (tmp != end())
		{
			cout << *tmp << " ";
			++tmp;
		}
		cout << endl;
	}

protected:
	//将[first,last)范围的元素移动到position之前
	void transfer(iter position, iter first, iter last)
	{
		if (position != last)
		{
			(link_type (last.node->prev))->next = position.node;
			(link_type (first.node->prev))->next = last.node;
			(link_type (position.node->prev))->next = first.node;

			link_type tmp = link_type (position.node->prev);

			position.node->prev = last.node->prev;
			last.prev->prev = first.node->prev;
			first.node->prev = tmp;
		}
	}
};

#endif
