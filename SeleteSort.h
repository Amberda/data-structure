#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;
#include <stdlib.h>

//÷±Ω”—°‘Ò≈≈–Ú
void SeleteSort(int* arr, int size)
{
	int i = 0;
	for (i = 0; i < size - 1; i++)
	{
		int index = i;
		for (int j = i + 1; j < size; j++)
		{
			if (arr[index]>arr[j])
			{
				index = j;
			}
		}
		if (index != i)
		{
			swap(arr[index], arr[i]);
		}
	}
}