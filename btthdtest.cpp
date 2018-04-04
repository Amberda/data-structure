#define _CRT_SECURE_NO_WARNINGS 1

#include "BinaryTreeThd.h"


void FunTest()
{
	char str1[] = "ABD#G###CE##F";
	ThdBinaryTree<char> bt1(str1, strlen(str1), '#');
	cout << "���������";
	bt1.InOrder();
	bt1.InOrderThreading();
	cout << "�������������:";
	bt1.InOrderThdNoR();

	char str2[] = "ABD#G###CE##F";
	ThdBinaryTree<char> bt2(str2, strlen(str2), '#');
	cout << "ǰ�����:";
	bt2.PreOrder();
	bt2.PreOrderThreading();
	cout << "ǰ�����������:";
	bt2.PreOrderThdNoR();
}

int main()
{
	FunTest();
	system("pause");
	return 0;
}