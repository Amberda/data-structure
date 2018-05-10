#define _CRT_SECURE_NO_WARNINGS 1

#include "BloomFilter.h"


void Test()
{
	BloomFilter<string> bf(10);
	bf.Insert("ŷ����");
	bf.Insert("ŷ����");
	bf.Insert("��ɵ��");
	bf.Insert("�󱦱�");
	cout << bf.Size() << endl;

	if (bf.IsInBloomFilter("�󱦱�"))
		cout << "�󱦱� ����" << endl;
	else
		cout << "�󱦱� ����" << endl;

	if (bf.IsInBloomFilter("³����"))
		cout << "³���� ����" << endl;
	else
		cout << "³���� ����" << endl;
}

int main()
{
	Test();
	system("pause");
	return 0;
}