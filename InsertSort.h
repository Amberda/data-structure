#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;
#include <stdlib.h>



//直接插入排序

// 最差时间复杂度 ---- 最坏情况为输入序列是降序排列的,此时时间复杂度O(n^2)
// 最优时间复杂度 ---- 最好情况为输入序列是升序排列的,此时时间复杂度O(n)
// 平均时间复杂度 ---- O(n^2)
// 空间复杂度 ------ O(1)
// 稳定性 ------------ 稳定

void InsertSort(int* array, int size)
{
	for (int i = 1; i < size ; i++)
	{
		int key = array[i];
		int j = i - 1;
		while (j >= 0 && key < array[j])
		{
			array[j + 1] = array[j];
			j--;
		}
		array[j + 1] = key;
	}
}

// 最差时间复杂度 ---- O(n^2)
// 最优时间复杂度 ---- O(nlogn)
// 平均时间复杂度 ---- O(n^2)
// 空间复杂度 ------ O(1)
// 稳定性 ------------ 稳定

void BinaryInsertSort(int* arr, int size)
{
	for (int i = 1; i < size; i++)
	{
		int left = 0;
		int right = i - 1;
		int key = arr[i];
		while (left <= right)
		{
			int mid = left + ((right - left) >> 1);
			if (arr[mid] > key)
			{
				right = mid - 1;
			}
			else
			{
				left = mid + 1;
			}
		}
		for (int j = i - 1; j >= left; j--)
		{
			arr[j + 1] = arr[j];
		}
		arr[left] = key;
	}
}