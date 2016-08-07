
#ifndef _MY_HASHTABLE_H_
#define _MY_HASHTABLE_H_
//----author:klaus
//----time:2016/8/7

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <cstddef>

using namespace std;
/*
hashtable节点
*/
template <class Value>
struct HashTableNode
{
	HashTableNode* next;
	Value val;
};

template <class Value, class Key, class HashFunc, class ExtractKey, class EqualKey>
class HashTable;

/*
hashtable迭代器
*/
template <class Value, class Key, class HashFunc, class ExtractKey, class EqualKey>
struct HashTableIterator 
{
	 typedef HashTable<Value, Key, HashFunc, ExtractKey, EqualKey> htb;
	 typedef HashTableIterator<Value, Key, HashFunc, ExtractKey, EqualKey> iter;
	 typedef HashTableNode<Value> node;

	 node* cur;

	 htb* ht;

	 HashTableIterator(node* n, htb* h) : cur(n), ht(h) { }
	 HashTableIterator() { }

	 Value& operator*() const { return cur->val; }
	 Value* operator->() const { return &(operator*()); }
	 
	 iter& operator++();
	 iter operator++(int);

	 bool operator==(const iter& it) const { return cur == it.cur; }
	 bool operator!=(const iter& it) const { return cur != it.cur; }
};

enum { stl_num_primes = 28 };

static const unsigned long stl_prime_list[stl_num_primes] =
{
	53ul,         97ul,         193ul,       389ul,       769ul,
	1543ul,       3079ul,       6151ul,      12289ul,     24593ul,
	49157ul,      98317ul,      196613ul,    393241ul,    786433ul,
	1572869ul,    3145739ul,    6291469ul,   12582917ul,  25165843ul,
	50331653ul,   100663319ul,  201326611ul, 402653189ul, 805306457ul, 
	1610612741ul, 3221225473ul, 4294967291ul
};

inline unsigned long GetNextPrime(unsigned long n)
{
	const unsigned long* first = stl_prime_list;
	const unsigned long* last = stl_prime_list + (int)stl_num_primes;
	const unsigned long* pos = std::lower_bound(first, last, n);
	return pos == last ? *(last - 1) : *pos;
}

/*
Value:节点的实值类型
Key:节点的键值类型
HashFunc:hash function的函数类型
ExtracKey:从节点中取出键值的方法
EqualKey:判断键值相同与否的方法
*/
template <class Value, class Key, class HashFunc, class ExtractKey, class EqualKey>
class HashTable 
{
private:
	typedef HashTableNode<Value> node;
	std::vector<node*> buckets;

	HashFunc hash;
	EqualKey equals;
	ExtractKey get_key;

	size_t num_elements;    //

	size_t NextSize(size_t n) const { return GetNextPrime(n); }

	void InitializeBuckets(size_t n)
	{
		const size_t n_buckets = NextSize(n);
		buckets.reserve(n_buckets);
		buckets.insert(buckets.end(), n_buckets, (node*) 0);
		num_elements = 0;
	}

public:
	 typedef HashTableIterator<Value, Key, HashFunc, ExtractKey, EqualKey> iter;

	 //构造函数
	 HashTable(size_t n, const HashFunc& hf, const EqualKey& eql, const ExtractKey& ext)
		 : hash(hf), equals(eql), get_key(ext), num_elements(0)
	 {
		 InitializeBuckets(n);
	 }
	 //构造函数
	HashTable(size_t n, const HashFunc& hf, const EqualKey& eql) 
		: hash(hf), equals(eql), get_key(ExtractKey()), num_elements(0)
	{
		InitializeBuckets(n);
	}

	HashTable(const HashTable& ht)
		: hash(ht.hash), equals(ht.equals), get_key(ht.get_key), num_elements(0)
	{
		CopyFrom(ht);
	}

	~HashTable() { Clear(); }

	size_t size() const { return num_elements; }

	//当前bucket vector的大小
	size_t BucketCount() const { return buckets.size(); }

	//bucket vector的size最大值
	size_t MaxBucketCount() const { return stl_prime_list[(int) stl_num_primes - 1]; }

	//计算buckets[n]里的节点数目
	size_t ElemsInBucket(const size_t n) const
	{
		size_t result = 0;
		for (node* cur = buckets[n]; cur; cur = cur->next)
		{
			result += 1;
		}
		return result;
	}

	node* GetNBuckets(const size_t n) const
	{
		return buckets[n];
	}

	//判断是否需要重建表格（bucket vector）
	void Resize(size_t num_elements_hint);

	//在不需要重建表格（bucket vector）的情况下加入节点，不允许重复
	std::pair<iter, bool> InsertUniqueNoresize(const Value& obj);

	//插入元素，不允许重复
	std::pair<iter, bool> InsertUnique(const Value& obj)
	{
		Resize(num_elements + 1);
		return InsertUniqueNoresize(obj);
	}

	//在不需要重建表格（bucket vector）的情况下加入节点，允许重复
	iter InsertEqualNoresize(const Value& obj);

	//插入元素，允许重复
	iter InsertEqual(const Value& obj)
	{
		Resize(num_elements + 1);
		return InsertEqualNoresize(obj);
	}

	//找到键值为k的元素
	iter Find(const Key& k)
	{
		size_t n = bkt_num_key(k);
		node* first = buckets[n];
		for ( ; first && !equals(get_key(first->val), k); first = first->next)
		{
			//和bucket list里的元素一一进行比较，若相等或者遇到null就退出循环
		}
		return iter(first, this);
	}

	//计算键值为k的元素的个数
	size_t Count(const Key& k) const
	{
		const size_t n = bkt_num_key(k);
		size_t result = 0;
		for (node* cur = buckets[n]; cur; cur = cur->next)
		{
			if (equals(get_key(cur->val), k))
			{
				++result;
			}
		}
		return result;
	}

	void Clear();

	iter Begin()
	{
		for (size_t n = 0; n < buckets.size(); ++n)
		{
			if (buckets[n])
			{
				return iter(buckets[n], this);
			}
		}
		return End();
	}

	iter End()
	{
		return iter(0, this);
	}

	//判断元素的落脚点
	size_t bkt_num(const Value& obj, size_t n) const
	{
		return bkt_num_key(get_key(obj), n);
	}

	size_t bkt_num(const Value& obj) const
	{
		return bkt_num_key(get_key(obj));
	}

	size_t bkt_num_key(const Key& k) const
	{
		return bkt_num_key(k, buckets.size());
	}

	size_t bkt_num_key(const Key& k, size_t n) const
	{
		return hash(k) % n;    //调用my_hash_fun.h文件中的hash function
	}

private:
	void CopyFrom(const HashTable& ht);
};

template <class Value, class Key, class HashFunc, class ExtractKey, class EqualKey>
HashTableIterator<Value, Key, HashFunc, ExtractKey, EqualKey>&
HashTableIterator<Value, Key, HashFunc, ExtractKey, EqualKey>::operator++()
{
	const node* old = cur;
	cur = cur->next;
	if (!cur)    //如果cur为空的话
	{
		size_t buc = ht->bkt_num(old->val);    //有一个问题：SGI源码中将成员函数bkt_num设置为private，那么按道理来说类的对象ht没有访问权限
		while (!cur && ++buc < ht->BucketCount())    //找出第一个buckets[buc]不为空的，即为下一个节点
		{
			cur = ht->GetNBuckets(buc);
		}
	}
	return *this;
}

template <class Value, class Key, class HashFunc, class ExtractKey, class EqualKey>
inline HashTableIterator<Value, Key, HashFunc, ExtractKey, EqualKey>
HashTableIterator<Value, Key, HashFunc, ExtractKey, EqualKey>::operator++(int)
{
	iter tmp = *this;
	++*this;
	return tmp;
}

template <class Value, class Key, class HashFunc, class ExtractKey, class EqualKey>
void HashTable<Value, Key, HashFunc, ExtractKey, EqualKey>::Resize(size_t num_elements_hint)
{
	const size_t old_n = buckets.size();
	if (num_elements_hint > old_n)
	{
		const size_t n = NextSize(num_elements_hint);

		if (n > old_n)
		{
			vector<node*> tmp(n, (node*) 0);

			for (size_t buc = 0; buc < old_n; ++buc)
			{
				node* first = buckets[buc];
				while (first)
				{
					size_t new_buc = bkt_num(first->val, n);

					buckets[buc] = first->next;
					first->next = tmp[new_buc];
					tmp[new_buc] = first;
					first = buckets[buc];
				}
			}
			buckets.swap(tmp);
		}
	}
}

template <class Value, class Key, class HashFunc, class ExtractKey, class EqualKey>
std::pair<typename HashTable<Value, Key, HashFunc, ExtractKey, EqualKey>::iter, bool>
HashTable<Value, Key, HashFunc, ExtractKey, EqualKey>::InsertUniqueNoresize(const Value& obj)
{
	const size_t n = bkt_num(obj);
	node* first = buckets[n];

	for (node* cur = first; cur; cur = cur->next)
		if ( equals(get_key(cur->val), get_key(obj)) )
			return std::pair<iter, bool>(iter(cur, this), false);

	node* tmp = (node*) malloc(sizeof(struct HashTableNode<Value>));
	tmp->val = obj;
	tmp->next = first;    //使新节点成为链表的第一个节点
	buckets[n] = tmp;
	++num_elements;

	return std::pair<iter, bool>(iter(tmp, this), true);
}

template <class Value, class Key, class HashFunc, class ExtractKey, class EqualKey>
typename HashTable<Value, Key, HashFunc, ExtractKey, EqualKey>::iter
HashTable<Value, Key, HashFunc, ExtractKey, EqualKey>::InsertEqualNoresize(const Value& obj)
{
	const size_t n = bkt_num(obj);
	node* first = buckets[n];

	for (node* cur = first; cur; cur = cur->next)
	{
		if ( equals(get_key(cur->val), get_key(obj)) )
		{
			//如果发现与链表中的键值相同，就进行插入操作，并返回
			node* tmp = (node*) malloc(sizeof(struct HashTableNode<Value>));
			tmp->val = obj;
			tmp->next = cur->next;    //新节点位于cur之后
			cur->next = tmp;
			++num_elements;

			return iter(tmp, this);
		}
	}

	node* tmp = (node*) malloc(sizeof(struct HashTableNode<Value>));
	tmp->next = first;    //使新节点成为链表的第一个节点
	buckets[n] = tmp;
	++num_elements;

	return iter(tmp, this);
}

template <class Value, class Key, class HashFunc, class ExtractKey, class EqualKey>
void HashTable<Value, Key, HashFunc, ExtractKey, EqualKey>::CopyFrom(const HashTable& ht)
{
	buckets.clear();
	buckets.reserve(ht.buckets.size());
	buckets.insert(buckets.end(), ht.buckets.size(), (node*) 0);

	for (size_t i = 0; i < ht.buckets.size(); ++i)
	{
		if (const node* cur = ht.buckets[i])
		{
			node* copy = (node*) malloc(sizeof(struct HashTableNode<Value>));
			copy->val = cur->val;
			buckets[i] = copy;

			for (node* next = cur->next; next; cur = next, next = cur->next)
			{
				copy->next = (node*) malloc(sizeof(struct HashTableNode<Value>));
				copy->next->val = next->val;
				copy = copy->next;
			}
		}
	}
	num_elements = ht.num_elements;
}

template <class Value, class Key, class HashFunc, class ExtractKey, class EqualKey>
void HashTable<Value, Key, HashFunc, ExtractKey, EqualKey>::Clear()
{
	for (size_t i = 0; i < buckets.size(); ++i)
	{
		node* cur = buckets[i];
		//将buckets list的每一个节点都删除
		while (cur != 0)
		{
			node* next = cur->next;
			free(cur);
			cur = next;
		}
		buckets[i] = 0;
	}
	num_elements = 0;
	//未释放掉buckets vector的空间
}

#endif     //! _MY_HASHTABLE_H_
