#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;
#include <stdlib.h>

void BubbleSort(int *arr, int size)
{
	for (int i = 0; i < size ; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (arr[i] < arr[j])
			{
				int tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
		}
	}
}