#define _CRT_SECURE_NO_WARNINGS 1

#include "BinaryTreeThd.h"


void FunTest()
{
	char str1[] = "ABD#G###CE##F";
	ThdBinaryTree<char> bt1(str1, strlen(str1), '#');
	cout << "中序遍历：";
	bt1.InOrder();
	bt1.InOrderThreading();
	cout << "中序遍历线索化:";
	bt1.InOrderThdNoR();

	char str2[] = "ABD#G###CE##F";
	ThdBinaryTree<char> bt2(str2, strlen(str2), '#');
	cout << "前序遍历:";
	bt2.PreOrder();
	bt2.PreOrderThreading();
	cout << "前序遍历线索化:";
	bt2.PreOrderThdNoR();
}

int main()
{
	FunTest();
	system("pause");
	return 0;
}