#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;
#include <stdlib.h>

template <class K, int M = 3>
struct BTreeNode
{
	K _key[M];               //关键字
	BTreeNode<K, M>* _subs[M + 1];  //孩子
	BTreeNode<K, M>* _parent;   
	size_t _size;               //key数量

	BTreeNode()
		:_parent(NULL)
		, _size(0)
	{
		for (size_t i = 0; i < M + 1; i++)
		{
			_subs[i] = NULL;
		}
	}
};

template <class K, int M = 3>
class BTree
{
	typedef BTreeNode<K, M> Node;
	typedef BTreeNode<K, M>* pNode;
public:

	BTree()
		:_pRoot(NULL)
	{}

	pair<pNode, K> Find(const K& key)
	{
		pNode cur = _pRoot;
		pNode parent = NULL;
		while (cur)
		{
			int i = 0;
			while (i < cur->_size&&cur->_key[i] < key)
			{
				++i;
			}
			
			if (cur->_key[i] == key)
				return pair<pNode, K>(cur, cur->_key[i]);
			//在孩子中找
			parent = cur;//标记双亲节点
			cur = cur->_subs[i];
		}
		return pair<pNode, K>(parent, -1);//返回插入节点可插入的位置
	}

	bool Insert(const K& key, pNode sub)
	{
		//树为空树
		if (_pRoot == NULL)
		{
			_pRoot = new Node;
			_pRoot->_key[0] = key;
			++_pRoot->_size;
			return true;
		}

		//树中已经存在和待插入元素相同的元素
		pair<pNode, K> ret = Find(key);
		if (ret.second != -1)
			return false;

		//插入元素
		K newkey = key;
		pNode cur = ret.first;  //待插入位置
		while (true)
		{
			//根据插入排序算法，找出位置
			int i = 0;
			for (i = cur->_size - 1; i >= 0; --i)
			{
				if (cur->_key[i] > newkey)
				{
					cur->_key[i + 1] = cur->_key[i];//移动关键字
					cur->_subs[i + 2] = cur->_subs[i + 1];//移动关键字的孩子
				}
				else
					break;
			}
			//插入节点
			cur->_key[i + 1] = newkey;
			//连接原来的孩子节点
			cur->_subs[i + 2] = sub;
			//更新双亲节点
			if (sub)
				(cur->_subs[i + 2])->_parent = cur;
			//调整元素个数
			++cur->_size;
			if (cur->_size < M)
				return true;

			//插入后关键字已满，需要分裂
			int mid = M / 2;
			//创建一个新节点
			pNode tmp = new Node;
			while (cur->_size > mid + 1)
			{
				tmp->_key[tmp->_size] = cur->_key[mid + 1];
				tmp->_subs[tmp->_size++] = cur->_subs[mid + 2];
				//tmp->_subs[tmp->_size]->_parent = tmp;
				--cur->_size;
			}
			cur->_size -= 1;
			//要分裂的节点是根节点
			if (cur->_parent == NULL)
			{
				_pRoot = new Node;
				_pRoot->_key[0] = cur->_key[mid];
				//左孩子是cur，右孩子是新节点
				_pRoot->_subs[0] = cur;
				_pRoot->_subs[1] = tmp;
				_pRoot->_size++;
				
				tmp->_parent = _pRoot;
				cur->_parent = _pRoot;
				return true;
			}
			//要分裂的节点不是根节点
			newkey = cur->_key[mid];
		
			cur = cur->_parent;
			sub = tmp;
			
		}
	}
private:
	pNode _pRoot;
};

