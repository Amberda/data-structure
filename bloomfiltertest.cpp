#define _CRT_SECURE_NO_WARNINGS 1

#include "BloomFilter.h"


void Test()
{
	BloomFilter<string> bf(10);
	bf.Insert("Å·Ñô·æ");
	bf.Insert("Å·Ñô¿Ë");
	bf.Insert("´óÉµ×Ó");
	bf.Insert("´ó±¦±´");
	cout << bf.Size() << endl;

	if (bf.IsInBloomFilter("´ó±¦±´"))
		cout << "´ó±¦±´ »µÈË" << endl;
	else
		cout << "´ó±¦±´ ºÃÈË" << endl;

	if (bf.IsInBloomFilter("Â³±¦±¦"))
		cout << "Â³±¦±¦ »µÈË" << endl;
	else
		cout << "Â³±¦±¦ ºÃÈË" << endl;
}

int main()
{
	Test();
	system("pause");
	return 0;
}