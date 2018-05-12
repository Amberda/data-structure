#pragma once

#include <iostream>
using namespace std;
#include <stdlib.h>
#include <vector>
#include <assert.h>


class UnionFindSet
{
public:

	UnionFindSet(size_t size)
	{
		_set.resize(size + 1);
		for (int i = 0; i < size+1; i++)
			_set[i] = -1;
	}

	void Union(int i, int j)
	{
		if (_set[i] < 0 && _set[j] < 0)
		{
			int root = i;
			_set[i] += _set[j];
			_set[j] = i;
		}
		else
		{
			int m = FindRoot(i);
			int n = FindRoot(j);

			_set[m] += _set[n];
			_set[n] = m;
		}
	}

	int FindRoot(int i)
	{
		assert(i >= 0);

		int k = i;
		while (_set[k] >= 0)
			k = _set[k];
		return k;
	}

	int SetCount()
	{
		int count = 0;
		for (int i = 0; i < _set.size(); i++)
		{
			if (_set[i] < 0)
				count++;
		}
		return count - 1;
	}

private:
	vector<int> _set;
};
