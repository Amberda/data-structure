#define _CRT_SECURE_NO_WARNINGS 1

#include "AVLTree.h"


void Test()
{
	int arr[10] = { 2, 5, 0, 6, 9, 1, 4, 3, 7, 8 };
	AVLTree<int, int> avl;
	for (int i = 0; i < 10; i++)
	{
		avl.Insert(arr[i], i);
	}
	avl.InOrder();

	cout << "avl is balance?" << avl.IsBalance() << endl;
	cout << "avlÊ÷¸ß¶ÈÎª£º" << avl.Height() << endl;

}

int main()
{
	Test();
	system("pause");
	return 0;
}