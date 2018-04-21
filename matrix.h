#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;
#include <vector>
#include <assert.h>
#include <memory.h>

//对称矩阵
template <class T, size_t N>
class SymmetricMatrix
{
public:
	SymmetricMatrix(T array[][N])
		:_row(N)
		, _col(N)
	{
		size_t index = 0;
		_array.resize(N*(N + 1) / 2);
		for (size_t i = 0; i < N; i++)
		{
			for (size_t j = 0; j <= i; j++)
			{
				_array[index++] = array[i][j];
			}
		}
	}
	const T& Acess(int row, int col)const
	{
		if (row < col)
			swap(row, col);
		size_t index = row*(row + 1) / 2 + col;
		return _array[index];
	}
	void Print()
	{
		for (size_t i = 0; i < _row; i++)
		{
			for (size_t j = 0; j < _col; j++)
			{
				if (i < j)
					cout << _array[j*(j + 1) / 2 + i] << " ";
				else if (i >= j)
				{
					cout << _array[i*(i + 1) / 2 + j] << " ";
				}
				//cout << Acess(i, j) << " ";
			}
			cout << endl;
		}
	}
	template <class T>
	friend ostream& operator<<(ostream& _cout, const SymmetricMatrix<T, N>& sm)
	{
		for (size_t i = 0; i < N; i++)
		{
			for (size_t j = 0; j < N; j++)
			{
				_cout << sm.Acess(i, j) << " ";
			}
		}
		return _cout;
	}
private:
	vector<T> _array;
	size_t _row;
	size_t _col;
};

//稀疏矩阵
template <class T>
class SparseMatrix
{
	template <class T>
	struct Trituple
	{
		Trituple()
		{}
		Trituple(size_t row, size_t col, T value)
		:_row(row)
		, _col(col)
		, _value(value)
		{}
		size_t _row;
		size_t _col;
		T _value;
	};
public:
	SparseMatrix()//无参构造函数
	{}
	SparseMatrix(int* arr, int row, int col, const T& invalid)
		:_row(row)
		, _col(col)
		, _invalid(invalid)
	{
		for (size_t i = 0; i < row; i++)
		{
			for (size_t j = 0; j < col; j++)
			{
				if (arr[i*col + j] != invalid)
				{
					_v.push_back(Trituple<T>(i, j, arr[i*col + j]));
				}
			}
		}
	}
	//访问稀疏矩阵中row行col列的元素
	const T& Acess(int row, int col)const
	{
		for (size_t i = 0; i < _v.size(); i++)
		{
			if (_v[i]._row == row&&_v[i]._col == col)
			{
				return _v[i]._value;
			}
		}
		return _invalid;
	}
	//还原稀疏矩阵
	template <class T>
	friend ostream& operator<<(ostream& _cout, const SparseMatrix<T>& sm)
	{
		size_t index = 0;
		for (size_t i = 0; i < sm._row; i++)
		{
			for (size_t j = 0; j < sm._col; j++)
			{
				if (index < sm._v.size() &&
					sm._v[index]._row == i&&sm._v[index]._col == j)
				{
					_cout << sm._v[index]._value << " ";
					index++;
				}
				else
				{
					_cout << sm._invalid << " ";

				}
			}
			_cout << endl;
		}
		return _cout;
	}
	//稀疏矩阵的转置 时间复杂度O(M*N)(M为元素个数N为矩阵列数)
	SparseMatrix<T>& Transport()
	{
		SparseMatrix<T>* sm = new SparseMatrix<T>;
		sm->_row = _col;
		sm->_col = _row;
		sm->_invalid = _invalid;
		for (size_t i = 0; i < _col; i++)
		{
			size_t index = 0;
			while (index < _v.size())
			{

				if (_v[index]._col == i)
				{
					sm->_v.push_back(Trituple<T>(i, _v[index]._row, _v[index]._value));
				}
				index++;
			}
		}
		return *sm;
		//SparseMatrix<T>* sm = new SparseMatrix<T>;
		//sm->_row = _col;
		//sm->_col = _row;
		//sm->_invalid = _invalid;
		//for (size_t i = 0; i < _col; i++)
		//{
		//	vector<Trituple<T>>::iterator it = _v.begin();
		//	while (it != _v.end())
		//	{
		//		if (it->_col == i)//从原矩阵第0列开始，将每列中的有效值依次放入新的稀疏矩阵  
		//			sm->_v.push_back(Trituple<T>(i, it->_row, it->_value));
		//		++it;
		//	}
		//}
		//return *sm;
	}
	//稀疏矩阵的快速转置 时间复杂度O(M+N)
	SparseMatrix<T>& FastTransport()
	{
		SparseMatrix<T>* sm = new SparseMatrix<T>;
		sm->_row = _col;
		sm->_col = _row;
		sm->_invalid = _invalid;
		sm->_v.resize(_v.size());

		//逆置成功后，新矩阵每行有效元素的个数
		int count[5];
		memset(count, 0, _col*sizeof(int));
		for (size_t i = 0; i < _v.size(); i++)
		{
			count[_v[i]._col]++;
		}
		//逆置成功后每行的起始地址
		int addr[5];
		memset(addr, 0, _col*sizeof(int));
		for (size_t i = 1; i < _col; i++)
		{
			addr[i] = addr[i - 1] + count[i - 1];
		}
		//放置元素
		for (size_t i = 0; i < _v.size(); i++)
		{
			sm->_v[addr[_v[i]._col]] = _v[i];
			swap(sm->_v[addr[_v[i]._col]]._row, sm->_v[addr[_v[i]._col]]._col);
			addr[_v[i]._col]++;
		}
		return *sm;
	}
	//稀疏矩阵的加法
	SparseMatrix<T> operator+(SparseMatrix<T>& sp)
	{
		//检测两个稀疏矩阵是否为同行同列
		assert(_row == sp._row&&_col == sp._col);
		SparseMatrix<T> ret;
		ret._row = _row;
		ret._col = _col;
		ret._invalid = _invalid;

		size_t Lindex = 0;
		size_t Rindex = 0;
		while (Lindex < _v.size() && Rindex < sp._v.size())
		{
			size_t AddrLeft = _v[Lindex]._row*_col + _v[Lindex]._col;
			size_t AddrRight = sp._v[Rindex]._row*sp._col + sp._v[Rindex]._col;
			if (AddrLeft < AddrRight)
			{
				ret._v.push_back(Trituple<T>(_v[Lindex]._row, _v[Lindex]._col, _v[Lindex]._value));
				Lindex++;
			}
			else if (AddrLeft >AddrRight)
			{
				ret._v.push_back(Trituple<T>(sp._v[Rindex]._row, sp._v[Rindex]._col, sp._v[Rindex]._value));
				Rindex++;
			}
			else
			{
				Trituple<T> tmp(_v[Lindex]._row, _v[Lindex]._col, _v[Lindex]._value + sp._v[Rindex]._value);

				if (tmp._value != _invalid)
				{
					ret._v.push_back(tmp);
				}
				Lindex++;
				Rindex++;
			}
		}
		while (Lindex < _v.size())
		{
			ret._v.push_back(_v[Lindex]);
			Lindex++;
		}
		while (Rindex < sp._v.size())
		{
			ret._v.push_back(sp._v[Rindex]);
			Rindex++;
		}
		return ret;
	}
private:
	vector<Trituple<T>> _v;
	size_t _row;
	size_t _col;
	T _invalid;
};