#define _CRT_SECURE_NO_WARNINGS 1

#include "UnionFindSet.h"


void Test1()
{
	UnionFindSet un(6);

	un.Union(1, 2);
	un.Union(2, 5);
	un.Union(3, 4);
	un.Union(1, 6);
	un.Union(1, 3);

	int count = un.SetCount();

}

int Friends(int m, int n, int a[][2])
{
	UnionFindSet T(m);

	for (int i = 0; i < n; i++)
	{
		T.Union(a[i][0], a[i][1]);
	}

	return T.SetCount();
}

void Test()
{
	int n = 5;
	int a[][2] = { { 1, 2 }, { 2, 3 }, { 4, 5 } };

	cout << "一共有" << Friends(5, 3, a) << "个朋友圈" << endl;

}

int main()
{
	Test1();
	system("pause");
	return 0;
}