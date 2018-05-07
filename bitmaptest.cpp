#define _CRT_SECURE_NO_WARNINGS 1

#include "BitMap.h"

void Test()
{
	BitMap bm(100);
	bm.Set(14);
	bm.Set(33);
	bm.Set(68);
	bm.Set(92);
	cout << "位集合中比特的个数：" << bm.Size() << endl;
	cout << "位集合中1的个数：" << bm.Count() << endl;

	bm.ReSet(68);
	cout << "位集合中比特的个数：" << bm.Size() << endl;
	cout << "位集合中1的个数：" << bm.Count() << endl;

	if (bm.Test(68))
		cout << "68比特位为1" << endl;
	else
		cout << "68比特位不为1" << endl;

	if (bm.Test(33))
		cout << "33比特位为1" << endl;
	else
		cout << "33比特位不为1" << endl;
}

int main()
{
	Test();
	system("pause");
	return 0;
}