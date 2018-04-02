#define _CRT_SECURE_NO_WARNINGS 1

#include "BSTree.h"


//void Test1()
//{
//	BSTree<int, int> bst;
//	int arr[10] = { 2, 5, 4, 7, 9, 1, 3, 8, 0, 6 };
//	for (int i = 0; i < 10; i++)
//	{
//		bst.Insert(arr[i], i);
//	}
//	bst.InOrder();
//
//	bst.Insert(10, 10);
//	bst.InOrder();
//
//	bst.DelNode(5);
//	bst.InOrder();
//
//	int min = bst.MostLNode();
//	int max = bst.MostRNode();
//	cout << "min = " << min << endl;
//	cout << "max = " << max << endl;
//	
//}

void Test2()
{
	BSTree<int, int> bst;
	int arr[10] = { 2, 5, 4, 7, 9, 1, 3, 8, 0, 6 };
	for (int i = 0; i < 10; i++)
	{
		bst.Insert(arr[i], i);
	}
	bst.InOrder();

	bst.Insert(10, 10);
	bst.InOrder();

	bst.Delete(5);
	bst.InOrder();

	//int min = bst.MostLNode();
	//int max = bst.MostRNode();
	//cout << "min = " << min << endl;
	//cout << "max = " << max << endl;

}


int main()
{
//	Test1();
	Test2();
	system("pause");
	return 0;
}