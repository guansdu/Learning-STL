#ifndef _MY_LIST_H_
#define  _MY_LIST_H_

#include <stdlib.h>
#include <cstddef>

struct SlistNodeBase
{
	SlistNodeBase* next;
};

template <class T>
struct SlistNode : public SlistNodeBase
{
	T data;
};


struct SlistIteratorBase 
{
	SlistNodeBase* node;

	SlistIteratorBase(SlistNodeBase* x) : node(x) { }
	
	void incr() { node = node->next; }

	bool operator==(const SlistIteratorBase& x) const { return node == x.node; }
	bool operator!=(const SlistIteratorBase& x) const { return node != x.node; }

};

template <class T, class Ref, class Ptr>
struct SlistIterator : public SlistIteratorBase
{
	typedef SlistIterator<T, T&, T*> iter;
	typedef SlistIterator<T, Ref, Ptr> self;

	typedef Ptr pointer;
	typedef Ref reference;

	typedef SlistNode<T> list_node;

	SlistIterator(list_node* x) : SlistIteratorBase(x) { }
	SlistIterator() : SlistIteratorBase(0) { }
	SlistIterator(const iter& x) : SlistIteratorBase(x.node) { }

	reference operator*() const { return ((list_node*) node)->data; }
	pointer operator->() const { return &(operator*()); }

	self& operator++()
	{
		incr();
		return *this;
	}
};

//使new_node位于prev_node之后
inline SlistNodeBase* MakeNodeLink(SlistNodeBase* prev_node, SlistNodeBase* new_node)
{
	new_node->next = prev_node->next;
	prev_node->next = new_node;
	return new_node;
}

inline size_t SlistSize(SlistNodeBase* node)
{
	size_t result = 0;
	for (; node != 0; node = node->next)
	{
		++result;
	}
	return result;
}

template <class T>
class Slist
{
public:
	typedef SlistIterator<T, T&, T*> iter;
private:
	typedef SlistNode<T> list_node;
	typedef SlistNodeBase list_node_base;

	list_node_base head;

public:
	Slist() { head.next = 0; }

	iter begin() { return iter( (list_node*) head.next );}
	iter end() { return iter(0); }
	size_t size() const { return SlistSize(head.next); }
	bool empty() const {return head.next == 0; }
	//返回首元素
	T& front() { return ((list_node*) head.next)->data; }

	//在首部插入一个元素
	void push_front(const T& x)
	{
		list_node* node = (list_node*) malloc (sizeof(struct list_node));
		node->data = x;
		MakeNodeLink(&head, node);
	}
	//在头部删除一个元素
	void pop_front()
	{
		list_node* tmp = (list_node*) head.next;
		head.next = tmp->next;
		free(tmp);
	}

	void print()
	{
		iter first = begin();
		cout << "slist: " ;
		while (first != end())
		{
			cout << *first << " ";
			++first;
		}
		cout << endl;
	}
};

#endif // !_MY_LIST_H_
