#pragma once

#include <iostream>
using namespace std;
#include <stdlib.h>
#include <vector>
#include <assert.h>
#include "UnionFindSet.h"
#include <queue>



#if 0
//�����ڽӾ���
template <class V, class W, bool IsDirect = false>
class Graph
{
public:
	Graph(V* arr, size_t size)
		:_v(arr, arr + size)
	{
		_edges.resize(size);
		for (size_t i = 0; i < size; i++)
		{
			_edges[i].resize(size);
		}
	}

	//�õ�v������
	size_t GetRootOfV(const V& v)
	{
		size_t N = _v.size();
		for (size_t i = 0; i < N; i++)
		{
			if (_v[i] == v)
				return i;
		}

		assert(false);
		return -1;
	}

	//��ӱ�
	void AddEdges(const V& v1, const V& v2, const W& weight)
	{
		size_t index1 = GetRootOfV(v1);
		size_t index2 = GetRootOfV(v2);

		_edges[index1][index2] = weight;
		if (!IsDirect)
			_edges[index2][index1] = weight;
	}

	//��һ����Ķ�
	size_t GetDegOfV(const V& v)
	{
		size_t count = 0;
		size_t N = _v.size();
		size_t index = GetRootOfV(v);
		for (size_t i = 0; i < N; i++)
		{
			if (_edges[index][i] != 0)
				count++;
		}
		if (!IsDirect)
		{
			for (size_t i = 0; i < N; i++)
			{
				if (_edges[i][index] != 0)
					count++;
			}
		}
		return count;
	}

	void PrintGraph()
	{
		size_t N = _v.size();
		for (size_t i = 0; i < N; i++)
		{
			cout << _v[i] << " ";
		}
		cout << endl;

		for (size_t i = 0; i < N; i++)
		{
			for (size_t j = 0; j < N; j++)
			{
				cout << _edges[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}

private:
	vector<V> _v;
	vector<vector<W>> _edges;
};
#endif


//�����ڽӱ�
template<class W>
struct Node
{
	struct Node* _next;
	W _weight;
	size_t _src;//���
	size_t _dst;//�յ�

	Node(size_t src, size_t dst, const W& weight)
		:_weight(weight)
		, _src(src)
		, _dst(dst)
		, _next(NULL)
	{}
};

template <class W>
class Compare
{
public:
	bool operator()(Node<W>* pLeft, Node<W>* pRight)
	{
		return pLeft->_weight < pRight->_weight;
	}
};


template <class V,class W,bool IsDirect=false>
class Graph
{
	typedef Node<W> node;
	typedef Node<W>* pNode;
	typedef Graph<V, W, IsDirect> Self;
public:

	Graph()
	{}

	Graph(V* arr, size_t size)
		:_v(arr, arr + size)
	{
		_edges.resize(size);
	}

	//�õ�v������
	size_t GetIndexOfV(const V& v)
	{
		size_t N = _v.size();
		for (size_t i = 0; i < N; i++)
		{
			if (_v[i] == v)
				return i;
		}

		assert(false);
		return -1;
	}

	//�жϵ�ǰ�ߴ治����
	bool CheakExist(const V& v1, const V& v2)
	{
		size_t index1 = GetIndexOfV(v1);
		size_t index2 = GetIndexOfV(v2);

		pNode cur = _edges[index1];
		while (cur != NULL)
		{
			if (cur->_dst == index2)
				return true;
			cur = cur->_next;
		}
		return false;
	}

	//�����
	void AddEdges(const V& v1, const V& v2, const W& weight)
	{
		size_t index1 = GetIndexOfV(v1);
		size_t index2 = GetIndexOfV(v2);

		if (CheakExist(v1, v2))
			return;
		_AddEdges(index1, index2, weight);
		if (!IsDirect)//����ͼ
			_AddEdges(index2, index1, weight);
	}

	//��һ������Ķ�
	size_t GetDegOfV(const V& v)
	{
		size_t index = GetIndexOfV(v);
		size_t count = 0;
		pNode cur = _edges[index];

		while (cur != NULL)
		{
			count++;
			cur = cur->_next;
		}

		//����ͼ
		if (!IsDirect)
			return count;
		else//����ͼ
		{
			for (size_t i = 0; i < _v.size(); i++)
			{
				pNode tmp = _edges[i];
				while (tmp != NULL)
				{
					if (tmp->_dst == index)
						count++;
					tmp = tmp->_next;
				}
			}
			return count;
		}
	}

	//ͼ�ı���---������ȱ���
	void GFS(const V& v)
	{
		queue<size_t> q;
		vector<bool> visited;
		size_t index = GetIndexOfV(v);
		size_t size = _v.size();

		visited.resize(size, false);

		for (size_t i = 0; i < size; i++)
		{
			if (visited[i] == false)
				_GFS(q, visited, i);
		}		
	}

	//ͼ�ı���---������ȱ���
	void DFS(const V& v)
	{
		size_t index = GetIndexOfV(v);
		vector<bool> visited;
		visited.resize(_v.size(), false);

		_DFS(visited, index);

		for (size_t i = 0; i < _v.size(); i++)
		{
			if (i == index)
				continue;
			if (visited[i] == true)
				continue;
			_DFS(visited, i);
		}
		cout << "NULL" << endl;
	}
	
	//��С������
	Self Kruska()
	{
		Self g;
		g._v = _v;
		vector<pNode> Edges;
		vector<pNode>::iterator it;
		for (it = _edges.begin(); it != _edges.end(); ++it)//ȡ�����еı�
		{
			pNode cur = *it;
			while (cur)
			{
				Edges.push_back(cur);
				cur = cur->_next;
			}
		}
		int count = Edges.size() - 1;
		sort(Edges.begin(), Edges.end(), Compare<W>());//ͨ��Ȩֵ�Ա߽�������

		UnionFindSet ufs(Edges.size());//�������鼯
		for (size_t i = 0; i < Edges.size(); i++)
		{
			count--;
			if (count == 0)
				break;
			ufs.Union(Edges[i]->_src, Edges[i]->_dst);
		}

		return g;
	}


private:
	void _AddEdges(size_t index1, size_t index2, const W& weight)
	{
		pNode NewNode = new node(index1, index2, weight);
		NewNode->_next = _edges[index1];
		_edges[index1] = NewNode;
	}

	void _GFS(queue<size_t>& q, vector<bool>& visited, size_t index)
	{
		q.push(index);
		while (!q.empty())
		{
			size_t front = q.front();
			q.pop();

			if (visited[front] == true)
				continue;
			cout << _v[front] << "--->";
			visited[front] = true;

			pNode cur = _edges[front];
			while (cur)
			{
				if (visited[cur->_dst] == false)
					q.push(cur->_dst);
				cur = cur->_next;
			}
		}
		cout << "NULL" << endl;
	}

	void _DFS(vector<bool>& visited, size_t index)
	{
		cout << _v[index] << "--->";
		visited[index] = true;

		pNode cur = _edges[index];
		while (cur)
		{
			if (visited[cur->_dst] == false)
				_DFS(visited, cur->_dst);
			cur = cur->_next;
		}
	}

private:
	vector<V> _v;
	vector<pNode> _edges;
};