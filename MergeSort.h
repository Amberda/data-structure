#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;
#include <stdlib.h>


void Merge(int* arr, int left, int mid, int right, int* tmp)
{
	int index1 = left;
	int index2 = mid;
	int index = left;

	while (index1 < mid&&index2 < right)
	{
		if (arr[index1] < arr[index2])
		{
			tmp[index++] = arr[index1++];
		}
		else
		{
			tmp[index++] = arr[index2++];
		}
	}
	while (index1 < mid)
		tmp[index++] = arr[index1++];
	while (index2 < right)
		tmp[index++] = arr[index2++];

	memcpy(arr + left, tmp + left, (right - left)*sizeof(int));

}
void _MergeSort(int* arr, int left, int right, int* tmp)
{
	if (right - left <= 1)
	{
		return;
	}
	if (left < right)
	{
		int mid = left + ((right - left) >> 1);
		_MergeSort(arr, left, mid, tmp);
		_MergeSort(arr, mid, right, tmp);
		Merge(arr, left, mid, right, tmp);
	}
}
void MergeSort(int* arr, int left, int right)
{
	int* tmp = new int[right - left];
	_MergeSort(arr, left, right, tmp);
	delete[] tmp;
}

void MergeSortNoR(int* arr, int size)
{	
	int* tmp = new int[size];
	int gap = 1;
	while (gap < size)
	{
		for (int i = 0; i < size; i += gap * 2)
		{
			int left = i;
			int mid = i + gap;
			int right = mid + gap;
			if (mid > size)
			{
				mid = size;
			}
			if (right > size)
			{
				right = size;
			}
			Merge(arr, left, mid, right, tmp);
		}
		gap *= 2;
	}
	delete[] tmp;
}
