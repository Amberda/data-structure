#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;
#include <stdlib.h>
#include <vector>
#include "comm.h"


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


template<class K, class V>
struct HashNode
{
	K _key;
	V _value;
	HashNode<K, V>* _next;

	HashNode(const K& key, const V& value)
		:_key(key)
		, _value(value)
		, _next(NULL)
	{}
};


template<class K, class V, class _HashFun>
class HashBucket;

//迭代器
template<class K, class V, class _HashFun = _HashFun<K>>
class HashBucketIterator
{
	typedef HashNode<K, V> Node;
	typedef HashNode<K, V>* pNode;
	typedef HashBucketIterator<K, V, _HashFun> Self;
public:
	
	HashBucketIterator()
		:_pCur(NULL)
		, _hb(NULL)
	{}
	
	HashBucketIterator(pNode pCur, HashBucket<K, V, _HashFun>* hb)
		:_pCur(pCur)
		, _hb(hb)
	{}

	HashBucketIterator(const Self& hbi)
		:_pCur(hbi._pCur)
		, _hb(hbi._hb)
	{}

	pair<K,V> operator*()
	{
		return make_pair(_pCur->_key, _pCur->_value);
	}

	pair<K, V>* operator->()
	{
		return &(operator*());
	}

	Self& operator++()//前置
	{
		Next();
		return *this;
	}

	Self operator++(int)//后置
	{
		Self tmp(*this);
		Next();
		return tmp;
	}

	bool operator ==(const Self& s) const
	{
		return _pCur == s._pCur&&_hb == s._hb;
	}

	bool operator !=(const Self& s) const
	{
		return !(*this == s);
	}

private:
	void Next()
	{
		if (_pCur->_next != NULL)
		{
			_pCur = _pCur->_next;
		}
		else
		{
			//找下一个非空桶的位置
			size_t bucketNo = _hb->HashFun(_pCur->_key) + 1;
			while (bucketNo < _hb->_table.capacity())
			{
				if (_hb->_table[bucketNo])
				{
					_pCur = _hb->_table[bucketNo];
					return;
				}
				++bucketNo;
			}
			_pCur = NULL;
		}
	}
private:
	pNode _pCur;
	HashBucket<K, V, _HashFun>* _hb;
};

template<class K, class V, class _HashFun = _HashFun<K>>
class HashBucket
{
	typedef HashNode<K, V> Node;
	typedef HashNode<K, V>* pNode;

	friend HashBucketIterator<K, V, _HashFun>;//声明为友元类，为了访问哈希桶中的私有成员
public:
	typedef HashBucketIterator<K, V, _HashFun> Iterator;
	HashBucket(size_t capacity = 10)
		:_size(0)
	{
		_table.resize(GetNextPrime(capacity));
	}

	Iterator Begin()
	{
		for (size_t i = 0; i < _table.capacity(); i++)
		{
			if (_table[i])
				return Iterator(_table[i], this);
		}
		return Iterator(NULL, this);
	}

	Iterator End()
	{
		return Iterator(NULL, this);
	}

	pair<Iterator,bool> InertEqual(const K& key, const V& value)
	{
		CheckCapacity();
		
		size_t bucketNo = HashFun(key);
		pNode cur = _table[bucketNo];

		if (cur == NULL)
		{
			cur = new Node(key, value);
			++_size;
			return make_pair(Iterator(cur, this), true);
		}
		
		pNode newNode = new Node(key, value);
		newNode->_next = _table[bucketNo];
		_table[bucketNo] = newNode;
		++_size;
		return make_pair(Iterator(newNode, this), true);
	}

	pair<Iterator,bool> InertUnique(const K& key, const V& value)
	{
		CheckCapacity();

		size_t bucketNo = HashFun(key);
		pNode cur = _table[bucketNo];

		if (cur == NULL)
		{
			cur = new Node(key, value);
			++_size;
			return make_pair(Iterator(cur, this), true);
		}
		while (cur)
		{
			if (cur->_key == key)
			{
				return make_pair(Iterator(cur, this), false);
			}
			cur = cur->_next;
		}
		pNode newNode = new Node(key, value);
		newNode->_next = _table[bucketNo];
		_table[bucketNo] = newNode;
		++_size;
		return make_pair(Iterator(newNode, this), true);
	}

	Iterator Find(const K& key)
	{
		if (_size == 0)
			return Iterator(cur, this);
		size_t addr = HashFun(key);
		pNode cur = _table[addr];
		while (cur)
		{
			if (cur->_key == key)
				return Iterator(cur, this);
			cur = cur->_next;
		}
		return Iterator(NULL, this);
	}

	bool DeleteEqual(const K& key)
	{
		size_t bucketNo = HashFun(key);
		pNode cur = _table[bucketNo];
		pNode pre = _table[bucketNo];
		size_t oldsize = _size;
		while (cur)
		{
			if (cur->_key == key)
			{
				if (_table[bucketNo] == cur)
				{
					_table[bucketNo] = cur->_next;
					delete cur;
					cur = _table[bucketNo];
				}
				else
				{
					pre->_next = cur->_next;
					delete cur;
					cur = pre->_next;
				}
				--_size;
			}
			else
			{
				pre = cur;
				cur = cur->_next;
			}
		}
		if (oldsize != _size)
			return true;
		return false;
	}

	bool DeleteUnique(const K& key)
	{
		size_t bucketNo = HashFun(key);
		pNode cur = _table[bucketNo];
		pNode pre = _table[bucketNo];;
		while (cur)
		{
			if (cur->_key == key)
			{
				if (_table[bucketNo] == cur)
					_table[bucketNo] = cur->_next;
				else
					pre->_next = cur->_next;
				delete cur;
				--_size;
				return true;
			}
			pre = cur;
			cur = cur->_next;
		}
		return false;
	}

	size_t Count(const K& key)
	{
		size_t bucketNo = _HashFun(key);
		pNode cur = _table[bucketNo];
		size_t count = 0;
		while (cur)
		{
			if (cur->_key == key)
				count++;
			cur = cur->_next;
		}
		return count;
	}

	size_t BucketSize(size_t bucketNo)
	{
		pNode cur = _table[bucketNo];
		size_t count = 0;
		while (cur)
		{
			count++;
			cur = cur->_next;
		}
		return count;
	}

	size_t Size()const
	{
		return _size;
	}

	bool Empty()const
	{
		return 0 == _size;
	}

	void Clear()
	{
		for (size_t i = 0; i < _table.capacity(); i++)
		{
			pNode cur = _table[i];
			while (cur)
			{
				_table[i] = cur->_next;
				delete cur;
				cur = _table[i];
				--_size;
			}
		}
	}

	V FindInsert(const K& key)
	{
		size_t addr = HashFun(key);
		pNode cur = _table[addr];
		while (cur)
		{
			if (cur->_key == key)
				return cur->_value
			cur = cur->_next;
		}
		pair<Iterator,bool> p = InertEqual(key, V());
		return (*(p.first)).second;
	}

	~HashBucket()
	{
		Clear();
	}
private:
	void CheckCapacity()
	{
		if (_size == _table.capacity())
		{
			size_t capacity = GetNextPrime(_table.capacity());
			HashBucket<K, V> newHash(capacity);

			for (size_t i = 0; i < _table.capacity(); i++)
			{
				pNode cur = _table[i];
				while (cur)
				{
					newHash.InertEqual(cur->_key, cur->_value);
					cur = cur->_next;
				}
			}
			Swap(newHash);
		}
	}

	size_t HashFun(const K& key)
	{
		_HashFun h;
		return h(key) % _table.capacity();
	}

	void Swap(HashBucket<K, V>& ht)
	{
		swap(_table, ht._table);
		swap(_size, ht._size);
	}

private:
	vector<pNode> _table;
	size_t _size;
};