#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;
#include <stdlib.h>

//Ï£¶ûÅÅÐò
void ShellSort(int* arr, int size)
{
	int gap = 1;
	while (gap < size)
	{
		gap = gap * 2 + 1;
	}
	while (gap>0)
	{
		for (int i = gap; i < size; i++)
		{

			int key = arr[i];
			int j = i - gap;
			while (j >= 0 && key < arr[j])
			{
				arr[j + 1] = arr[j];
				j = j - gap;
			}
			arr[j + gap] = key;
		}
		gap = gap / 3;
	}
}