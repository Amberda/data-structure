#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;
#include <stdlib.h>
#include <stack>


//取中间的元素
int GetMidData(int* arr, int left, int right)
{
	int mid = left + ((right - left) >> 1);
	if (arr[left] < arr[right - 1])
	{
		if (arr[left]>arr[mid])
			return left;
		else if (arr[right - 1] < arr[mid])
			return right - 1;
		else
			return mid;
	}
	else
	{
		if (arr[left]<arr[mid])
			return left;
		else if (arr[right - 1] > arr[mid])
			return right - 1;
		else
			return mid;
	}
}

//方式一  hoare法
size_t Pation1(int* arr, int left, int right)
{
	int begin = left;
	int end = right - 1;
	int index = GetMidData(arr, left, right);
	int key = arr[index];
	if (index != end)
	{
		swap(arr[index], arr[end]);
	}
	while (begin < end)
	{
		while (begin < end&&arr[begin] <= key)
			begin++;
		while (begin < end&&arr[end] >= key)
			end--;
		if (begin < end)
		{
			swap(arr[begin], arr[end]);
		}
	}
	if (begin < right)
	{
		swap(arr[begin], arr[right-1]);
	}
	return begin;
}

//方式二 挖坑法
size_t Pation2(int* arr, int left, int right)
{
	int begin = left;
	int end = right - 1;
	int index = GetMidData(arr, left, right);
	int key = arr[index];
	if (index != end)
	{
		swap(arr[index], arr[end]);
	}
	
	while (begin < end)
	{
		while (begin < end&&arr[begin] <= key)
			begin++;
		if (begin < end)
			arr[end] = arr[begin];
		while (begin < end&&arr[end] >= key)
			end--;
		if (begin < end)
			arr[begin] = arr[end];
	}
	arr[begin] = key;
	return begin;
}

//方式三
size_t Pation3(int* arr, int left, int right)
{
	int cur = 0;
	int pre = cur - 1;
	int index = GetMidData(arr, left, right);
	int key = arr[index];
	if (index != right-1)
	{
		swap(arr[index], arr[right-1]);
	}

	for (int i = 0; i < right; i++)
	{
		if (arr[cur] < key && ++pre != cur)
		{
			swap(arr[pre], arr[cur]);
		}
		cur++;
	}
	if (++pre != right)
	{
		swap(arr[pre], arr[right-1]);
	}
	return pre;
}
//递归版本
void QuickSort(int* arr, int left, int right)
{
//	if (right - left < 16)//元素少的时候用插入排序
//	{
//		//InsertSort()
//	}
//	else
//	{
		if (left < right)
		{
			size_t div = Pation2(arr, left, right);
			QuickSort(arr, left, div);
			QuickSort(arr, div + 1, right);
		}
//	}
}

//非递归
void QuickSort_NoR(int * arr, int size)
{
	int left = 0;
	int right = size - 1;

	stack<int> s;
	s.push(right);
	s.push(left);

	while (!s.empty())
	{
		left = s.top();
		s.pop();
		right = s.top();
		s.pop();
		if (left < right)
		{
			int div = Pation2(arr, left, right);
			//保存右半部分的区间 
			s.push(right);
			s.push(div + 1);
			//保存左半部分的区间
			s.push(div);
			s.push(left);
		}
	}

}
