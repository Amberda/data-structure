#define _CRT_SECURE_NO_WARNINGS 1

#include "QuickSort.h"
#include "BubbleSort.h"

void Test()
{
	int arr[10] = { 2, 0, 4, 9, 3, 6, 8, 7, 1, 5 };
	QuickSort(arr, 0, 10);

	int arr2[10] = { 2, 0, 4, 9, 3, 6, 8, 7, 1, 5 };
	BubbleSort(arr2, 10);
}

int main()
{
	Test();
	system("pause");
	return 0;
}