#include <iostream>
using namespace std;
#include <stdlib.h>
#include <vector>

//���
template<class T>
class MaxHeap
{
public:
	MaxHeap()
	{}
	MaxHeap(T* arr, size_t n)
	{
		_arr.reserve(n);
		//_arr.resize(n);
		for (size_t i = 0; i < n; i++)
		{
			_arr.push_back(arr[i]);
			//_arr[i] = arr[i];
		}
		//����
		for (int i = (_arr.size - 2) / 2; i >= 0; --1)
		{
			AdjustDown(i);
		}
	}
	//���µ���
	void AdjustDown(int root)
	{
		int parent = root;
		int child = parent * 2 + 1;//���ӽڵ��±�
		while (child < _arr.size())
		{
			if (child + 1 < _arr.size() && _arr[child + 1] > _arr[child])//�����Һ����нϴ����һ��
			{
				++child;
			}
			//�жϸ��׺ͺ��ӵĴ�С
			if (_arr[child] > _arr[parent])
			{
				swap(_arr[parent], _arr[child]);
				parent = child;
				child = parent * 2 + 1;
			}
			else
			{
				break;
			}
		}
	}
	//���ϵ���
	void AdjustUp(int child)
	{
		int parent = (child - 1) / 2;
		while (parent >= 0)
		{
			if (_arr[parent] > _arr[child])
			{
				swap(_arr[parent], _arr[child]);
				child = parent;
				parent = (child - 1) / 2;
			}
			else
			{
				break;
			}
		}
	}
	void Push(const T& d)
	{
		_arr.push_back(d);
		AdjustUp(_arr.size() - 1);
	}
	void Pop()
	{
		if (!_arr.empty())
		{
			swap(_arr[0], _arr[_arr.size() - 1]);
			_arr.pop_back();
			AdjustDown(0);
		}
	}
	size_t Size()
	{
		return _arr.size();
	}
	bool Empty()
	{
		return _arr.empty();
	}
	T&Top()const
	{
		return _arr[0];
	}

private:
	vector<T> _arr;
};


//С��
template<class T>
class MinHeap
{
public:
	MinHeap()
	{}
	MinHeap(T* arr, size_t n)
	{
		_arr.reserve(n);
		for (size_t i = 0; i < n; i++)
		{
			_arr.push_back(arr[i]);
		}
		//����
		for (int i = (_arr.size() - 2) / 2; i >= 0; --1)//�ӵ�����һ����Ҷ�ӽڵ㿪ʼ����
		{
			AdjustDown(i);
		}
	}
	//���µ���
	void AdjustDown(int root)
	{
		int parent = root;
		int child = parent * 2 + 1;//���ӽڵ��±�
		while (child < _arr.size())
		{
			if (child + 1 < _arr.size() && _arr[child + 1] < _arr[child])//�����Һ����н�С����һ��
			{
				++child;
			}
			//�жϸ��׺ͺ��ӵĴ�С
			if (_arr[child] < _arr[parent])
			{
				swap(_arr[parent], _arr[child]);
				parent = child;
				child = parent * 2 + 1;
			}
			else
			{
				break;
			}
		}
	}
	//���ϵ���
	void AdjustUp(int child)
	{
		int parent = (child - 1) / 2;
		while (parent >= 0)
		{
			if (_arr[parent] < _arr[child])
			{
				swap(_arr[parent], _arr[child]);
				child = parent;
				parent = (child - 1) / 2;
			}
			else
			{
				break;
			}
		}
	}
	void Push(const T& d)
	{
		_arr.push_back(d);
		AdjustUp(_arr.size() - 1);
	}
	void Pop()
	{
		if (!_arr.empty())
		{
			swap(_arr[0], _arr[_arr.size() - 1]);
			_arr.pop_back();
			AdjustDown(0);
		}
	}
	size_t Size()
	{
		return _arr.size();
	}
	bool Empty()
	{
		return _arr.empty();
	}
	T& Top()
	{
		return _arr[0];
	}

private:
	vector<T> _arr;
};


//���÷º���,��ߴ���ĸ�����
template <class T>
struct Greater
{
	bool operator()(const T& left, const T& right)
	{
		return left > right;
	}
};
template <class T>
struct Less
{
	bool operator()(const T& left, const T& right)
	{
		return left < right;
	}
};

template<class T, class Compare = Greater<T> >
class Heap
{
public:
	Heap()
	{}
	Heap(const T* arr, size_t n)
	{
		_arr.reserve(n);
		for (size_t i = 0; i < n; i++)
		{
			_arr.push_back(arr[i]);
		}
		//����
		for (int i = (_arr.size() - 2) / 2; i >= 0; --i)
		{
			AdjustDown(i);
		}
	}
	//���µ���
	void AdjustDown(int root)
	{
		int parent = root;
		int child = parent * 2 + 1;//���ӽڵ��±�
		Compare com;
		while (child < _arr.size())
		{
			if (child + 1 < _arr.size() && com(_arr[child + 1], _arr[child]))//�����Һ����н�С/�����һ��
			{
				++child;
			}
			//�жϸ��׺ͺ��ӵĴ�С
			if (com(_arr[child], _arr[parent]))
			{
				swap(_arr[parent], _arr[child]);
				parent = child;
				child = parent * 2 + 1;
			}
			else
			{
				break;
			}
		}
	}
	//���ϵ���
	void AdjustUp(int child)
	{
		Compare com;
		int parent = (child - 1) / 2;
		while (parent >= 0) //while (child > 0)
		{
			if (com(_arr[child], _arr[parent]))
			{
				swap(_arr[parent], _arr[child]);
				child = parent;
				parent = (child - 1) / 2;
			}
			else
			{
				break;
			}
		}
	}
	void Push(const T& d)
	{
		_arr.push_back(d);
		AdjustUp(_arr.size() - 1);
	}
	void Pop()
	{
		if (!_arr.empty())
		{
			swap(_arr[0], _arr[_arr.size() - 1]);
			_arr.pop_back();
			AdjustDown(0);
		}
	}
	size_t Size()
	{
		return _arr.size();
	}
	bool Empty()
	{
		return _arr.empty();
	}
	T& Top()
	{
		return _arr[0];
	}

private:
	vector<T> _arr;
};

