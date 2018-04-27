#pragma once

#include "HashBucket.h"


template<class K, class V, class _HashFun = _HashFun<K>>
class unorderedMap
{
public:
	typename typedef HashBucket<K, V>::Iterator Iterator;
public:
	unorderedMap()
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

	pair<Iterator, bool> Insert(const K& key, const V& value)
	{
		return _ht.InertUnique(key, value);
	}

	pair<Iterator, bool> Erase(const K& key)
	{
		return _ht.DeleteUnique(key);
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
		_ht.Clear();
	}

	Iterator Find(const  K& key)
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

	V operator[](const K& key)
	{
		return _ht.FindInsert(key);
	}

private:
	HashBucket<K, V> _ht;
};