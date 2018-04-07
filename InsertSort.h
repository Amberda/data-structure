#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;
#include <stdlib.h>



//ֱ�Ӳ�������

// ���ʱ�临�Ӷ� ---- ����Ϊ���������ǽ������е�,��ʱʱ�临�Ӷ�O(n^2)
// ����ʱ�临�Ӷ� ---- ������Ϊ�����������������е�,��ʱʱ�临�Ӷ�O(n)
// ƽ��ʱ�临�Ӷ� ---- O(n^2)
// �ռ临�Ӷ� ------ O(1)
// �ȶ��� ------------ �ȶ�

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

// ���ʱ�临�Ӷ� ---- O(n^2)
// ����ʱ�临�Ӷ� ---- O(nlogn)
// ƽ��ʱ�临�Ӷ� ---- O(n^2)
// �ռ临�Ӷ� ------ O(1)
// �ȶ��� ------------ �ȶ�

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