#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;
#include <stdlib.h>

template <class K, int M = 3>
struct BTreeNode
{
	K _key[M];               //�ؼ���
	BTreeNode<K, M>* _subs[M + 1];  //����
	BTreeNode<K, M>* _parent;   
	size_t _size;               //key����

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
			//�ں�������
			parent = cur;//���˫�׽ڵ�
			cur = cur->_subs[i];
		}
		return pair<pNode, K>(parent, -1);//���ز���ڵ�ɲ����λ��
	}

	bool Insert(const K& key, pNode sub)
	{
		//��Ϊ����
		if (_pRoot == NULL)
		{
			_pRoot = new Node;
			_pRoot->_key[0] = key;
			++_pRoot->_size;
			return true;
		}

		//�����Ѿ����ںʹ�����Ԫ����ͬ��Ԫ��
		pair<pNode, K> ret = Find(key);
		if (ret.second != -1)
			return false;

		//����Ԫ��
		K newkey = key;
		pNode cur = ret.first;  //������λ��
		while (true)
		{
			//���ݲ��������㷨���ҳ�λ��
			int i = 0;
			for (i = cur->_size - 1; i >= 0; --i)
			{
				if (cur->_key[i] > newkey)
				{
					cur->_key[i + 1] = cur->_key[i];//�ƶ��ؼ���
					cur->_subs[i + 2] = cur->_subs[i + 1];//�ƶ��ؼ��ֵĺ���
				}
				else
					break;
			}
			//����ڵ�
			cur->_key[i + 1] = newkey;
			//����ԭ���ĺ��ӽڵ�
			cur->_subs[i + 2] = sub;
			//����˫�׽ڵ�
			if (sub)
				(cur->_subs[i + 2])->_parent = cur;
			//����Ԫ�ظ���
			++cur->_size;
			if (cur->_size < M)
				return true;

			//�����ؼ�����������Ҫ����
			int mid = M / 2;
			//����һ���½ڵ�
			pNode tmp = new Node;
			while (cur->_size > mid + 1)
			{
				tmp->_key[tmp->_size] = cur->_key[mid + 1];
				tmp->_subs[tmp->_size++] = cur->_subs[mid + 2];
				//tmp->_subs[tmp->_size]->_parent = tmp;
				--cur->_size;
			}
			cur->_size -= 1;
			//Ҫ���ѵĽڵ��Ǹ��ڵ�
			if (cur->_parent == NULL)
			{
				_pRoot = new Node;
				_pRoot->_key[0] = cur->_key[mid];
				//������cur���Һ������½ڵ�
				_pRoot->_subs[0] = cur;
				_pRoot->_subs[1] = tmp;
				_pRoot->_size++;
				
				tmp->_parent = _pRoot;
				cur->_parent = _pRoot;
				return true;
			}
			//Ҫ���ѵĽڵ㲻�Ǹ��ڵ�
			newkey = cur->_key[mid];
		
			cur = cur->_parent;
			sub = tmp;
			
		}
	}
private:
	pNode _pRoot;
};

