#pragma once

#include <iostream>
using namespace std;
#include <vector>


class BitMap
{
public:
	BitMap(size_t size = 10)
		:_size(size)
	{
		_bitmap.resize((size >> 5) + 1);
	}
	//将位图的某一位置1
	void Set(size_t whichbit)
	{
		size_t index = (whichbit >> 5);
		size_t  bit = whichbit % 32;
		if (whichbit < _size)
			_bitmap[index] |= (1 << bit);
	}
	//将位图的某一位置0
	void ReSet(size_t whichbit)
	{
		size_t index = (whichbit >> 5);
		size_t bit = whichbit % 32;
		if (whichbit < _size)
			_bitmap[index] &= ~(1 << bit);
	}
	//判断某一个数在位图中是否存在
	bool Test(size_t whichbit)
	{
		size_t index = whichbit >> 5;
		size_t bit = whichbit % 32;
		if (whichbit < _size)//换成assert来判断
			return (_bitmap[index] & (1 << bit));
		return false;//有可能是元素不存在返回false
	}
	//返回位图中有效元素的个数
	size_t Count()
	{
		//可以调用Test函数来一个位一个位的的判断
		//还可以查表，利用哈希的思想
		char* pBitCount = "\0\1\1\2\1\2\2\3\1\2\2\3\2\3\3\4";
		size_t count = 0;
		for (int i = 0; i < _size; i++)
		{
			int value = _bitmap[i];
			int j = 0;
			while (j < sizeof(int))
			{
				count += pBitCount[value & 0x0f];//取出低四个比特位，判断在表中1的个数，加到count上
				value >>= 4;
				count += pBitCount[value & 0x0f];
				value >> 4;//统计完一个字节
				j++;
			}
		}
		return count;
	}
	size_t Size()const
	{
		return _size;
	}
private:
	vector<int> _bitmap;
	size_t _size;//bit的位数
};