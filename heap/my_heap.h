//author:Klaus
//time:2016/7/15

#ifndef _MY_HEAP_H
#define  _MY_HEAP_H

#include <vector>
#include<stddef.h>

template <typename T>
void MakeHeap(typename std::vector<T>::iterator first, typename std::vector<T>::iterator last)
{
	//长度为0或者1时，不需要任何操作
	if (last - first < 2)
		return ;
	//待建堆的元素个数
	ptrdiff_t len = last - first;
	//只需要对非叶子结点进行重排即可，找到最后一个非叶子结点
	//这里下标从0开始，所以最后一个非叶子结点下标为(len-2)/2
	//注意：vector的范围是[first,last)，半闭半开区间，所以这里不是(len-1)/2
	ptrdiff_t parent = (len - 2) / 2;

	while (true)
	{
		AdjustHeap<T>(first, parent, len, T(*(first + parent)));
		if (parent == 0)
		{
			return;
		}
		parent--;
	}
}

template <typename T>
void PushHeap(typename std::vector<T>::iterator first, typename std::vector<T>::iterator last)
{
	//新插入的值已经放入了vector的尾部，则初始空洞结点就是vector的尾端元素
	//topIndex为根结点的下标，这里设置为0
	_PushHeap<T>( first, ptrdiff_t((last - first) - 1), 0, T(*(last - 1)) );
}

template <typename T>
void _PushHeap(typename std::vector<T>::iterator first, ptrdiff_t holeIndex, ptrdiff_t topIndex, T value)
{
	//找到空洞元素的父结点
	ptrdiff_t parent = (holeIndex -1) / 2;
	//未到达根结点，且父结点的值小于value
	while (holeIndex > topIndex && *(first + parent) < value)
	{
		//把父结点的值赋给空洞结点
		*(first + holeIndex) = *(first + parent);
		//设置新的空洞结点
		holeIndex = parent;
		//新的空洞结点的父结点
		parent = (holeIndex - 1) / 2;
	}

	*(first + holeIndex) = value;
}


template <typename T>
void PopHeap(typename std::vector<T>::iterator first, typename std::vector<T>::iterator last)
{
	//value用来保存尾结点的值
	T value = T(*(last-1));
	//将尾结点的值设置为首结点的值，这样我们就可以用pop_back操作取出
	*(last-1) = *first;
	//第二个参数ptrdiff_t holeIndex：初始空洞结点就是0，即为根结点；
	//第三个参数ptrdiff_t len：对区域[first,last-1)进行调整，使之符合堆的性质
	AdjustHeap<T>(first, 0, ptrdiff_t(last - first - 1), value);
}

template <typename T>
void AdjustHeap(typename std::vector<T>::iterator first, ptrdiff_t holeIndex, ptrdiff_t len, T value)
{
	//保存根结点的下标
	ptrdiff_t topIndex = holeIndex;
	//初始为空洞结点的右子结点
	ptrdiff_t bigChild = 2*holeIndex+2;
	while (bigChild < len)
	{
		//比较空洞结点左右子大小，使之成为较大的子结点
		if (*(first + bigChild) < *(first + bigChild - 1))
			bigChild--;
		//把大的子结点赋值给空洞结点
		*(first + holeIndex) = *(first + bigChild);
		holeIndex = bigChild;
		//为新空洞结点的右子结点
		bigChild = 2 * holeIndex + 2;
	}
	if (bigChild == len)
	{
		*(first + holeIndex) = *(first + bigChild - 1);
		holeIndex = bigChild - 1;
	}
	//这里直接用*(first+holeIndex) = value是不正确的，侯捷的书中有误。
	//注意：最后将value放在最后的空洞结点位置时，要再执行一次percolate up上溯操作
	//因为直接赋值后可能不满足堆的性质。
	_PushHeap<T>(first, holeIndex, topIndex, value);
}

template <typename T>
void SortHeap(typename std::vector<T>::iterator first, typename std::vector<T>::iterator last)
{
	//第一次执行PopHeap，最大值就被放在vector的尾端
	//扣除尾端再执行一次PopHeap，次大值又被放在尾端
	//如此反复，即可得到递增序列
	while (last - first > 1)
	{
		PopHeap<T>(first, last--);
	}
}


#endif //_MY_HEAP_H
