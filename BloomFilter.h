#pragma once

#include "BitMap.h"

class KeyToInt1
{
public:
	size_t operator()(const string& s)
	{
		return SDBMHash(s.c_str());
	}
private:
	size_t SDBMHash(const char *str)
	{
		register size_t hash = 0;
		while (size_t ch = (size_t)*str++)
		{
			hash = 65599 * hash + ch;
			//hash = (size_t)ch + (hash << 6) + (hash << 16) - hash;  
		}
		return hash;
	}
};

class KeyToInt2
{
public:
	size_t operator()(const string& s)
	{
		return RSHash(s.c_str());
	}
private:
	size_t RSHash(const char *str)
	{
		register size_t hash = 0;
		size_t magic = 63689;
		while (size_t ch = (size_t)*str++)
		{
			hash = hash * magic + ch;
			magic *= 378551;
		}
		return hash;
	}
};

class KeyToInt3
{
public:
	size_t operator()(const string& s)
	{
		return APHash(s.c_str());
	}
private:
	size_t APHash(const char *str)
	{
		register size_t hash = 0;
		size_t ch;
		for (long i = 0; ch = (size_t)*str++; i++)
		{
			if ((i & 1) == 0)
			{
				hash ^= ((hash << 7) ^ ch ^ (hash >> 3));
			}
			else
			{
				hash ^= (~((hash << 11) ^ ch ^ (hash >> 5)));
			}
		}
		return hash;
	}
};

class KeyToInt4
{
public:
	size_t operator()(const string& s)
	{
		return JSHash(s.c_str());
	}
private:
	size_t JSHash(const char*str)
	{
		if (!*str)        // 这是由本人添加，以保证空字符串返回哈希值0  
			return 0;
		register size_t hash = 1315423911;
		while (size_t ch = (size_t)*str++)
		{
			hash ^= ((hash << 5) + ch + (hash >> 2));
		}
		return hash;
	}
};

class KeyToInt5
{
public:
	size_t operator()(const string& s)
	{
		return DEKHash(s.c_str());
	}
private:
	size_t DEKHash(const char* str)
	{
		if (!*str)        // 这是由本人添加，以保证空字符串返回哈希值0  
			return 0;
		register size_t hash = 1315423911;
		while (size_t ch = (size_t)*str++)
		{
			hash = ((hash << 5) ^ (hash >> 27)) ^ ch;
		}
		return hash;
	}
};


template<class K, class KToInt1 = KeyToInt1, class KToInt2 = KeyToInt2, 
         class KToInt3 = KeyToInt3, class KToInt4 = KeyToInt4, class KToInt5 = KeyToInt5>
class BloomFilter
{
public:

	BloomFilter(size_t size)
		:_bm(10 * size)
		, _size(0)
	{}

	void Insert(const K& key)
	{
		size_t bitCount = _bm.Size();

		size_t index1 = KToInt1()(key) % bitCount;
		size_t index2 = KToInt2()(key) % bitCount;
		size_t index3 = KToInt3()(key) % bitCount;
		size_t index4 = KToInt4()(key) % bitCount;
		size_t index5 = KToInt5()(key) % bitCount;

		_bm.Set(index1);
		_bm.Set(index2);
		_bm.Set(index3);
		_bm.Set(index4);
		_bm.Set(index5);

		++_size;
	}

	bool IsInBloomFilter(const K& key)
	{
		size_t bitCount = _bm.Size();

		size_t index1 = KToInt1()(key) % bitCount;
		if (!_bm.Test(index1))
			return false;

		size_t index2 = KToInt2()(key) % bitCount;
		if (!_bm.Test(index2))
			return false;

		size_t index3 = KToInt3()(key) % bitCount;
		if (!_bm.Test(index3))
			return false;

		size_t index4 = KToInt4()(key) % bitCount;
		if (!_bm.Test(index4))
			return false;

		size_t index5 = KToInt5()(key) % bitCount;
		if (!_bm.Test(index5))
			return false;

		return true;//有可能在
	}

	size_t Size()const
	{
		return _size;
	}

private:
	BitMap _bm;
	size_t _size;
};