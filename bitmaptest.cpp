#define _CRT_SECURE_NO_WARNINGS 1

#include "BitMap.h"

void Test()
{
	BitMap bm(100);
	bm.Set(14);
	bm.Set(33);
	bm.Set(68);
	bm.Set(92);
	cout << "λ�����б��صĸ�����" << bm.Size() << endl;
	cout << "λ������1�ĸ�����" << bm.Count() << endl;

	bm.ReSet(68);
	cout << "λ�����б��صĸ�����" << bm.Size() << endl;
	cout << "λ������1�ĸ�����" << bm.Count() << endl;

	if (bm.Test(68))
		cout << "68����λΪ1" << endl;
	else
		cout << "68����λ��Ϊ1" << endl;

	if (bm.Test(33))
		cout << "33����λΪ1" << endl;
	else
		cout << "33����λ��Ϊ1" << endl;
}

int main()
{
	Test();
	system("pause");
	return 0;
}