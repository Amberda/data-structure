#define _CRT_SECURE_NO_WARNINGS 1

#pragma once
#include <iostream>
using namespace std;
#include <stack>
#include <assert.h>
struct Pos
{
	int _x;
	int _y;
	bool operator==(Pos pos)
	{
		if (pos._x == _x&&pos._y == _y)
		{
			return true;
		}
		return false;
	}
	bool operator!=(Pos pos)
	{
		if (pos._x == _x&&pos._y == _y)
		{
			return false;
		}
		return true;
	}
};


class Maze
{
public:
	//初始化迷宫
	Maze(int maze[][10])
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				_maze[i][j] = maze[i][j];
				//_maze[i][j] = maze[i * 10 + j];传参就应该传一维数组 int* maze
			}
		}
	}
	//打印迷宫
	void PrintMaze()
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				cout << _maze[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
	//入口是否合法
	bool IsEntry(Pos entry)
	{
		if (_maze[entry._x][entry._y] == 1)
		{
			return true;
		}
		return false;
	}
	//当前位置是否为通路
	bool IsPass(Pos cur)
	{
		if (_maze[cur._x][cur._y] == 1)
		{
			return true;
		}
		return false;
	}
	//是否为出口
	//bool IsExit(Pos pos)
	//{
	//	if (pos._x < 0 || pos._x >= 10 || pos._y < 0 || pos._y >= 10)
	//	{
	//		return true;
	//	}
	//	return false;
	//}
	bool IsExit(Pos pos)
	{
		if (pos._x == 0 || pos._x == 9 || pos._y == 0 || pos._y == 9)
		{
			return true;
		}
		return false;
	}
	bool IsPass(Pos cur, Pos next)
	{
		if ((next._x < 10 && next._y<10) && 
			(_maze[next._x][next._y] == 1 || _maze[next._x][next._y]>_maze[cur._x][cur._y]))
		{
			return true;
		}
		return false;
	}
	
	bool GetPath(Pos entry)
	{
		//if (!IsEntry(entry))//检测入口是否正确
		//{
		//	return false;
		//}
		Pos cur = entry;
		Pos next = entry;
		stack<Pos> s;
		s.push(cur);
		//stack<Pos> s1;
		//s1.push(entry);
		
		while (!s.empty())
		{
			cur = s.top();
			//_maze[cur._x][cur._y] = 2;//标记走过的路
			if (cur._x == 0)
			{
				if (shortPath.empty() || s.size() < shortPath.size())
				{
					shortPath = s;
				}
				cout << "找到一个出口" << '[' << entry._x << ',' << entry._y << ']' << endl;
				s.pop();
				//return true;
				continue;
			}
		/*    if (cur != entry&&IsExit(cur))
			{
				_maze[cur._x][cur._y] = 2;
				return true;
			}*/
			//if (cur._x == 0)
			//{
			//	return true;
			//}
			//上
			Pos up = cur;
			up._x -= 1;
			if (IsPass(cur,up))
			{
				_maze[up._x][up._y] = _maze[cur._x][cur._y] + 1;
				s.push(up);
				continue;
			}

			//左
			Pos left = cur;
			left._y -= 1;
			if (IsPass(cur,left))
			{
				_maze[left._x][left._y] = _maze[cur._x][cur._y] + 1;
				s.push(left);
				continue;
			}

			//右
			Pos right = cur;
			right._y += 1;
			if (IsPass(cur,right))
			{
				_maze[right._x][right._y] = _maze[cur._x][cur._y] + 1;
				s.push(right);
				continue;
			}

			//下
			Pos down = cur;
			down._x += 1;
			if (IsPass(cur,down))
			{
				_maze[down._x][down._y] = _maze[cur._x][cur._y] + 1;
				s.push(down);
				continue;
			}
			_maze[cur._x][cur._y] = 3;
			s.pop();//弹出走不通的路
		}
		return false;
	}

	//递归实现
	void GetPathR(Pos entry,stack<Pos>& s)
	{
		if (s.empty())
			_maze[entry._x][entry._y] = 2;
		s.push(entry);
		//if (s.empty()&&IsExit(entry))
		if (entry._x == 0)
		{
			if (shortPath.empty() || s.size() < shortPath.size())
			{
				shortPath = s;
			}
			cout << "找到一个出口" << '[' << entry._x << ',' << entry._y << ']' << endl;
			//return;
		}
		Pos cur = entry;
		//if (cur != entry&&IsExit(entry))
		//{
		//	cout << "找到一个出口" << '[' << entry._x << ',' << entry._y << ']' << endl;
		//	return;
		//}

		//上
		Pos up = cur;
		up._x -= 1;
		if (IsPass(entry, up))
		{
			_maze[up._x][up._y] = _maze[entry._x][entry._y] + 1;
			s.push(up);
			GetPathR(up, s);
		}

		//左
		Pos left = cur;
		left._y -= 1;
		if (IsPass(entry, left))
		{
			_maze[left._x][left._y] = _maze[entry._x][entry._y] + 1;
			GetPathR(left, s);
		}

		//右
		Pos right = cur;
		right._y += 1;
		if (IsPass(entry, right))
		{
			_maze[right._x][right._y] = _maze[entry._x][entry._y] + 1;
			GetPathR(right, s);
		}

		//下
		Pos down = cur;
		down._x += 1;
		if (IsPass(entry, down))
		{
			_maze[down._x][down._y] = _maze[entry._x][entry._y] + 1;
			GetPathR(down, s);
		}
		s.pop();
	}


private:
	int _maze[10][10];
	stack<Pos> shortPath;
};

