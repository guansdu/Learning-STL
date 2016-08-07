#include <iostream>

#include "my_equal_key.h"
#include "my_extract_key.h"
#include "my_hash_fun.h"
#include "my_hashtable.h"

using namespace std;

int main()
{
	HashTable<int, int, Hash<int>, Identity<int>, EqualTo<int>> iht(50, Hash<int>(), EqualTo<int>());

	cout << iht.size() <<endl;
	cout << iht.BucketCount() << endl;
	cout << iht.MaxBucketCount() << endl;

	iht.InsertUnique(59);
	iht.InsertUnique(63);
	iht.InsertUnique(108);
	iht.InsertUnique(2);
	iht.InsertUnique(53);
	iht.InsertUnique(55);

	cout << iht.size() <<endl;

	HashTable<int, int, Hash<int>, Identity<int>, EqualTo<int>>::iter ite = iht.Begin();

	for (int i = 0; i < iht.size(); ++i, ++ite)
	{
		cout << *ite << " ";
	}
	cout << endl;
	
	cout << *iht.Find(59) << endl;
	cout << iht.Count(59) << endl;

	for (int i = 0; i < iht.BucketCount(); ++i)
	{
		int n = iht.ElemsInBucket(i);
		if (n != 0)
		{
			cout << "buckets[" << i  << "] has " << n << " elems." << endl;
		}
	}

	for (int i = 0; i <= 47; ++i)
	{
		iht.InsertEqual(i);
	}
	cout << iht.size() <<endl;
	cout << iht.BucketCount() << endl;

	system("pause");
	return 0;
}
