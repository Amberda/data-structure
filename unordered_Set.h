#pragma once

#include "HashBucket.h"


template<class K, class _HashFun = _HashFun<K>>
class unorderedSet
{
public:
	typename typedef HashBucket<K, K>::Iterator Iterator;
public:
	unorderedSet()
		:_ht()
	{}

	Iterator Begin()
	{
		return _ht.Begin();
	}

	Iterator End()
	{
		return _ht.End();
	}

	pair<Iterator, bool> Insert(const K& key, const K& value)
	{
		return _ht.InertEqual(key, value);
	}

	pair<Iterator, bool> Erase(const K& key)
	{
		return _ht.DeleteEqual(key);
	}

	size_t Size()const
	{
		return _ht.Size();
	}

	bool Empty()const
	{
		return _ht.Empty();
	}

	void Clear()
	{
		return _ht.Clear();
	}

	Iterator Find(const K& key)
	{
		return _ht.Find(key);
	}

	size_t Count(const K& key)
	{
		return _ht.Count(key);
	}

	size_t BucketCount()
	{
		return _ht._size;
	}

	size_t BucketSize(size_t bucketNo)
	{
		return _ht.BucketSize(bucketNo);
	}

	K operator[](const K& key)
	{
		return _ht.FindInsert(key);
	}

private:
	HashBucket<K, K> _ht;
};