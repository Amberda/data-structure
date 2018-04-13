#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;
#include <stdlib.h>

//堆排序

void AdjustDown(int *arr, int n, int size)
{
	size_t parent = n;
	size_t child = 2 * n + 1;
	while (child < size)
	{
		if ((child + 1 < size) && (arr[child + 1] > arr[child]))
		{
			++child;
		}
		if (arr[child]>arr[parent])
		{
			swap(arr[parent], arr[child]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			break;
		}
	}
}
void HeapSort(int *arr, size_t n)
{
	//建堆
	int i = 0;
	for (i = (n - 2) / 2; i >= 0; --i)
	{
		AdjustDown(arr, i, n);
	}
	//选数据
	for (int j = n - 1; j > 0; --j)
	{
		swap(arr[0], arr[j]);
		AdjustDown(arr, 0, j);
	}
}


