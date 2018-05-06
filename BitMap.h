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
	//��λͼ��ĳһλ��1
	void Set(size_t whichbit)
	{
		size_t index = (whichbit >> 5);
		size_t  bit = whichbit % 32;
		if (whichbit < _size)
			_bitmap[index] |= (1 << bit);
	}
	//��λͼ��ĳһλ��0
	void ReSet(size_t whichbit)
	{
		size_t index = (whichbit >> 5);
		size_t bit = whichbit % 32;
		if (whichbit < _size)
			_bitmap[index] &= ~(1 << bit);
	}
	//�ж�ĳһ������λͼ���Ƿ����
	bool Test(size_t whichbit)
	{
		size_t index = whichbit >> 5;
		size_t bit = whichbit % 32;
		if (whichbit < _size)//����assert���ж�
			return (_bitmap[index] & (1 << bit));
		return false;//�п�����Ԫ�ز����ڷ���false
	}
	//����λͼ����ЧԪ�صĸ���
	size_t Count()
	{
		//���Ե���Test������һ��λһ��λ�ĵ��ж�
		//�����Բ�����ù�ϣ��˼��
		char* pBitCount = "\0\1\1\2\1\2\2\3\1\2\2\3\2\3\3\4";
		size_t count = 0;
		for (int i = 0; i < _size; i++)
		{
			int value = _bitmap[i];
			int j = 0;
			while (j < sizeof(int))
			{
				count += pBitCount[value & 0x0f];//ȡ�����ĸ�����λ���ж��ڱ���1�ĸ������ӵ�count��
				value >>= 4;
				count += pBitCount[value & 0x0f];
				value >> 4;//ͳ����һ���ֽ�
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
	size_t _size;//bit��λ��
};