#include<iostream>
#include<vector>
//author: Klaus
//time: 2016/7/12

using namespace std;

int main()
{
	cout << "----init:" << endl;
	vector<int> iv(2,9);
	cout << "size:" << iv.size() << endl;				//2
	cout << "capacity:" << iv.capacity() << endl;		//2

	cout << "----push_buck 1:" << endl;
	iv.push_back(1);
	cout << "size:" << iv.size() << endl;				//3
	cout << "capacity:" << iv.capacity() << endl;		//3	

	cout << "----push_buck 2:" << endl;
	iv.push_back(2);
	cout << "size:" << iv.size() << endl;				//4
	cout << "capacity:" << iv.capacity() << endl;		//4

	cout << "----push_buck 3:" << endl;
	iv.push_back(3);
	cout << "size:" << iv.size() << endl;				//5
	cout << "capacity:" << iv.capacity() << endl;		//6

	cout << "----push_buck 4:" << endl;
	iv.push_back(4);
	cout << "size:" << iv.size() << endl;				//6
	cout << "capacity:" << iv.capacity() << endl;		//6
	
	cout << "----push_buck 5:" << endl;
	iv.push_back(5);
	cout << "size:" << iv.size() << endl;				//7
	cout << "capacity:" << iv.capacity() << endl;		//9

	cout << "----now the vector:" << endl;
	for(int i = 0; i < iv.size(); i++)
		cout << iv[i] << " ";							//9 9 1 2 3 4
	cout << endl;

	cout << "----do pop_back:" << endl;
	iv.pop_back();
	cout << "size:" << iv.size() << endl;				//6
	cout << "capacity:" << iv.capacity() << endl;		//9

	cout << "----do pop_back:" << endl;
	iv.pop_back();
	cout << "size:" << iv.size() << endl;				//5
	cout << "capacity:" << iv.capacity() << endl;		//9

	cout << "----do pop_back:" << endl;
	iv.pop_back();
	cout << "size:" << iv.size() << endl;				//4
	cout << "capacity:" << iv.capacity() << endl;		//9

	cout << "----now the vector:" << endl;
	for(int i = 0; i < iv.size(); i++)
		cout << iv[i] << " ";							//9 9 1 2
	cout << endl;

	cout << "----erase 1:" << endl;
	vector<int>::iterator ivite = find(iv.begin(), iv.end(), 1);
	if (ivite != iv.end())
	{
		iv.erase(ivite);
	}
	cout << "size:" << iv.size() << endl;				//3
	cout << "capacity:" << iv.capacity() << endl;		//9

	cout << "----now the vector:" << endl;
	for(int i = 0; i < iv.size(); i++)
		cout << iv[i] << " ";							//9 9 2
	cout << endl;

	cout << "----insert triple 7 before 2:" << endl;
	ivite = find(iv.begin(), iv.end(), 2);
	if (ivite != iv.end())
	{
		iv.insert(ivite, 3, 7);
	}
	cout << "size:" << iv.size() << endl;				//6
	cout << "capacity:" << iv.capacity() << endl;		//9

	cout << "----now the vector(use at):" << endl;
	for(int i = 0; i < iv.size(); i++)
		cout << iv.at(i) << " ";						//9 9 7 7 2
	cout << endl;

	cout << "----whether the vector is empty:" << endl;
	cout << iv.empty() << endl;							//0

	cout << "----get the front and back of vector:" << endl;
	cout << iv.front() << "," << iv.back() << endl;		//9,2

	cout << "----use the reverse iterator:" << endl;
	vector<int>::reverse_iterator rit = iv.rbegin();
	for (; rit!= iv.rend(); ++rit)
		cout << *rit << " ";							//2 7 7 7 9 9
	cout << endl;
	
	cout << "----use reserve:" << endl;
	iv.reserve(15);
	cout << "size:" << iv.size() << endl;				//6
	cout << "capacity:" << iv.capacity() << endl;		//15
	cout << "max size:" << iv.max_size() << endl;		//1073741823

	iv.clear();
	cout << "size:" << iv.size() << endl;				//0
	cout << "capacity:" << iv.capacity() << endl;		//15

	getchar();
	return 0;
}
