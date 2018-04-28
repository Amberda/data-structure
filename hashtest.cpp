#define _CRT_SECURE_NO_WARNINGS 1

//#include "HashTable.h"
//#include "HashBucket.h"
#include "unordered_Map.h"
#include <string>

//void TestHashTable1()
//{
//	HashTable<int> ht;
//	ht.Insert(12);
//	ht.Insert(32);
//	ht.Insert(17);
//	ht.Insert(45);
//	ht.Insert(61);
//
//	ht.Delete(12);
//	ht.Insert(22);
//
//}
//
//void TestHashTable2()
//{
//	HashTable<string> ht;
//	ht.Insert("1111");
//	ht.Insert("2222");
//	ht.Insert("3333");
//	ht.Insert("4444");
//	ht.Insert("abcd");
//	ht.Insert("最最");
//
//	if (-1 != ht.Find("最最"))
//		cout << "In HashTale" << endl;
//	else
//		cout << "Not In HashTable" << endl;
//}

//void TestHashBucket()
//{
//	HashBucket<int,int> hb;
//
//	hb.InertUnique(12, 12);
//	hb.InertEqual(12, 12);
//	hb.InertUnique(35, 35);
//	hb.InertUnique(71, 71);
//	hb.InertUnique(26, 26);
//	hb.InertUnique(88, 88);
//	hb.InertUnique(65, 65);
//
//
//	hb.DeleteUnique(26);
//	hb.DeleteEqual(12);
//
//	HashBucketIterator<int, int> it = hb.Begin();
//	while (it != hb.End())
//	{
//		cout << *it << " ";
//		++it;
//	}
//	cout << endl;
//
//	HashBucket<string, string> hb2;
//
//	hb2.InertUnique("1111", "1111");
//	hb2.InertEqual("1111", "1111");
//	hb2.InertUnique("2222", "2222");
//	hb2.InertUnique("3333", "3333");
//	hb2.InertUnique("4444", "4444");
//	hb2.InertUnique("5555", "5555");
//
//
//	hb2.DeleteUnique("4444");
//	hb2.DeleteEqual("2222");
//
//} 

void TestUnorderedMap()
{
	unorderedMap<string,string> un;

	un.Insert("1111", "1111");
	un.Insert("2222", "2222");
	un.Insert("3333", "3333");
	un.Insert("4444", "4444");
	un.Insert("5555", "5555");

	cout << un["4444"] << endl;
	cout << un["5555"] << endl;

	unorderedMap<string, string>::Iterator it = un.Begin();


}

int main()
{
//	TestHashTable1();
//	TestHashTable2();
//	TestHashBucket();
	TestUnorderedMap();
	system("pause");
	return 0;
}