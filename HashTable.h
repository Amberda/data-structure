#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;
#include <stdlib.h>
#include "comm.h"

#define MAX_SIZE 10

typedef enum State
{
	EMPTY,
	EXSIT,
	DELETE
}State;

template <class K>
struct Elem
{
	K _key;
	State _state;
};

//��̬�汾  ����̽��  ��ϣ��
#if 0
template <class K>
class HashTable
{
public:

	HashTable()
		:_size(0)
	{
		for (int i = 0; i < MAX_SIZE; i++)
			_hashtable[i]._state = EMPTY;
	}

	bool Insert(const K& key)
	{
		size_t hashaddr = HashFun(key);
		size_t start = hashaddr;
		while(_hashtable[hashaddr]._state != EMPTY)
		{
			if (_hashtable[hashaddr]._state == EXSIT&&key == _hashtable[hashaddr]._key)
			{
				return false;
			}
			hashaddr++;
			if (hashaddr == start)
				return false;
			if (hashaddr == MAX_SIZE)
				hashaddr = 0;
		}
		
		_hashtable[hashaddr]._key = key;
		_hashtable[hashaddr]._state = EXSIT;
		_size++;
		return true;
	}

	int Find(const K& key)
	{
		size_t hashaddr = HashFun(key);
		int start = hashaddr;
		while (_hashtable[hashaddr]._state != EMPTY)
		{
			if (_hashtable[hashaddr]._state == EXSIT)
			{
				if (_hashtable[hashaddr]._key == key)
					return hashaddr;
			}
			hashaddr++;
			if (hashaddr == start)
				return -1;
			if (hashaddr == MAX_SIZE - 1)
				hashaddr = 0;
		}
		return -1;
	}

	bool Delete(const K& key)
	{
		int ret = Find(key);
		if (ret != -1)
		{
			_hashtable[ret]._state = DELETE;
			--_size;
			return true;
		}
		return false;
	}

private:

	size_t HashFun(const K& key)
	{
		return key%MAX_SIZE;
	}

private:
	Elem<K> _hashtable[MAX_SIZE];
	size_t _size;
};
#endif

//��̬�汾  ����̽�� ����̽��
#if 0
template <class K, bool IsLine = true>
class HashTable
{
public:

	HashTable()
		:_size(0)
	{
		for (int i = 0; i < MAX_SIZE; i++)
			_hashtable[i]._state = EMPTY;
	}

	bool Insert(const K& key)
	{
		size_t hashaddr = HashFun(key);

		//��������
		if (_size * 10 / MAX_SIZE >= 7)
			return false;

		size_t i = 1;
		while (_hashtable[hashaddr]._state != EMPTY)
		{
			if (_hashtable[hashaddr]._state == EXSIT&&key == _hashtable[hashaddr]._key)
			{
				return false;
			}
			
			//����̽��
			if (IsLine)
				LineCheck(hashaddr);
			//����̽��
			else
				SecondCheck(hashaddr, i++);//��һ��ģ������жϸ�������̽�⻹�Ƕ���̽��
			//hashaddr++;
			//if (hashaddr == start)
			//	return false;
			//if (hashaddr == MAX_SIZE)
			//	hashaddr = 0;
		}

		_hashtable[hashaddr]._key = key;
		_hashtable[hashaddr]._state = EXSIT;
		_size++;
		return true;
	}

	int Find(const K& key)
	{
		size_t hashaddr = HashFun(key);
		int i = 1;
		while (_hashtable[hashaddr]._state != EMPTY)
		{
			if (_hashtable[hashaddr]._state == EXSIT)
			{
				if (_hashtable[hashaddr]._key == key)
					return hashaddr;
			}
			//����̽��
			if (IsLine)
				LineCheck(hashaddr);
			//����̽��
			else
				SecondCheck(hashaddr, i++);//��һ��ģ������жϸ�������̽�⻹�Ƕ���̽��
			//hashaddr++;
			//if (hashaddr == start)
			//	return -1;
			//if (hashaddr == MAX_SIZE - 1)
			//	hashaddr = 0;
		}
		return -1;
	}

	bool Delete(const K& key)
	{
		int ret = Find(key);
		if (ret != -1)
		{
			_hashtable[ret]._state = DELETE;
			--_size;
			return true;
		}
		return false;
	}

	size_t Size()
	{
		return _size;
	}
	bool Empty()
	{
		return _size == 0;
	}

private:

	size_t HashFun(const K& key)
	{
		return key%MAX_SIZE;
	}
	//����̽��
	void LineCheck(size_t& hashaddr)
	{
		++hashaddr;
		if (hashaddr >= MAX_SIZE)
			hashaddr = 0;
	}
	//����̽��
	void SecondCheck(size_t& hashaddr,size_t i)
	{
		hashaddr = hashaddr + ((i << 1) + 1);
		if (hashaddr >= MAX_SIZE)
			hashaddr %= MAX_SIZE;
	}

private:
	Elem<K> _hashtable[MAX_SIZE];
	size_t _size;
};
#endif


template <class K>
struct _HashFun
{
	size_t operator()(const K& key)
	{
		return key;
	}
};

template <>
struct _HashFun<string>
{
public:
	size_t operator()(const string& str)
	{
		return BKDRHash(str.c_str());
	}
private:
	static size_t BKDRHash(const char * str)
	{
		unsigned int seed = 131; // 31 131 1313 13 131 1313 13  
		unsigned int hash = 0;
		while (*str)
		{
			hash = hash * seed + (*str++);
		}
		return(hash & 0x7FFFFFFF);
	}
};
//��̬�汾
//����������---����
#if 1
template <class K, bool IsLine = true, class _HashFun = _HashFun<K>>
class HashTable
{
public:

	HashTable(size_t capacity = 10)
		:_size(0)
	{
		capacity = GetNextPrime(capacity);
		_hashtable = new Elem<K>[capacity];
		_capacity = capacity;
		for (int i = 0; i < capacity; i++)
			_hashtable[i]._state = EMPTY;
	}

	bool Insert(const K& key)
	{
		CheckCapacity();
		size_t hashaddr = HashFun(key);
		size_t i = 1;
		while (_hashtable[hashaddr]._state != EMPTY)
		{
			if (_hashtable[hashaddr]._state == EXSIT&&key == _hashtable[hashaddr]._key)
			{
				return false;
			}

			//����̽��
			if (IsLine)
				LineCheck(hashaddr);
			//����̽��
			else
				SecondCheck(hashaddr, i++);//��һ��ģ������жϾ�������̽�⻹�Ƕ���̽��
		}

		_hashtable[hashaddr]._key = key;
		_hashtable[hashaddr]._state = EXSIT;
		_size++;
		return true;
	}

	int Find(const K& key)
	{
		size_t hashaddr = HashFun(key);
		int i = 1;
		while (_hashtable[hashaddr]._state != EMPTY)
		{
			if (_hashtable[hashaddr]._state == EXSIT)
			{
				if (_hashtable[hashaddr]._key == key)
					return hashaddr;
			}
			//����̽��
			if (IsLine)
				LineCheck(hashaddr);
			//����̽��
			else
				SecondCheck(hashaddr, i++);//��һ��ģ������жϸ�������̽�⻹�Ƕ���̽��
		}
		return -1;
	}

	bool Delete(const K& key)
	{
		int ret = Find(key);
		if (ret != -1)
		{
			_hashtable[ret]._state = DELETE;
			--_size;
			return true;
		}
		return false;
	}
	~HashTable()
	{
		if (_hashtable)
		{
			delete[] _hashtable;
			_size = 0;
			_capacity = 0;
		}
	}
	size_t Size()
	{
		return _size;
	}
	bool Empty()
	{
		return _size == 0;
	}
private:

	void CheckCapacity()
	{
		//��������
		if (_size * 10 / _capacity >= 7)
		{
			//����
			size_t newcapacity = GetNextPrime(_capacity);
			HashTable<K> newHash(newcapacity);//����һ����ʱ�Ĺ�ϣ��
			for (size_t i = 0; i < _capacity; ++i)//���ƾɹ�ϣ���е�Ԫ��
			{
				if (_hashtable[i]._state == EXSIT)
				{
					newHash.Insert(_hashtable[i]._key);
				}
			}
			Swap(newHash);
		}
	}

	size_t HashFun(const K& key)
	{
		//return key%_capacity;
		_HashFun h;
		return h(key) % _capacity;
	}
	//����̽��
	void LineCheck(size_t& hashaddr)
	{
		++hashaddr;
		if (hashaddr >= _capacity)
			hashaddr = 0;
	}
	//����̽��
	void SecondCheck(size_t& hashaddr, size_t i)
	{
		hashaddr = hashaddr + ((i << 1) + 1);
		if (hashaddr >= _capacity)
			hashaddr %= _capacity;
	}

	void Swap(HashTable<K>& ht)
	{
		swap(_hashtable, ht._hashtable);
		swap(_capacity, ht._capacity);
		swap(_size, ht._size);
	}

private:
	Elem<K>* _hashtable;
	size_t _size;
	size_t _capacity;
};
#endif