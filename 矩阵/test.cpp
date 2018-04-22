#define _CRT_SECURE_NO_WARNINGS 1

#include "matrix.h"

void FunTest()
{
	int a[5][5] = {
		{ 0, 1, 2, 3, 4 },
		{ 1, 0, 1, 2, 3 },
		{ 2, 1, 0, 1, 2 },
		{ 3, 2, 1, 0, 1 },
		{ 4, 3, 2, 1, 0 } 
	};
	SymmetricMatrix<int, 5> m(a);
	//m.Print();
	//cout << m.Acess(1, 0) << endl;
	cout << m << endl;
}
void FunTest1()
{
	int a[6][5] = {
		{ 1, 0, 3, 0, 5 },
		{ 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0 },
		{ 1, 0, 3, 0, 5 },
		{ 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0 } 
	};
	SparseMatrix<int> sp1((int*)a, 6, 5, 0);
	cout << sp1.Acess(3, 4) << endl;
	cout << sp1 << endl;

	SparseMatrix<int> sp2;
	sp2 = sp1.Transport();
	cout << "sp1的转置：" << endl;
	cout << sp2 << endl;

	sp2 = sp1.FastTransport();
	cout << "sp1的快速转置：" << endl;
	cout << sp2 << endl;

}

void FunTest2()
{
	int a[6][5] = {
		{ 1, 0, 3, 0, 5 },
		{ 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0 },
		{ 1, 0, 3, 0, 5 },
		{ 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0 }
	};
	int a1[6][5] = {
		{ 1, 3, 0, 0, 5 },
		{ 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0 },
		{ 1, 0, -3, 0, 5 },
		{ 0, 1, 0, 0, 0 },
		{ 0, 0, 0, 0, 0 }
	};
	SparseMatrix<int> sp1((int*)a, 6, 5, 0);
	SparseMatrix<int> sp2((int*)a1, 6, 5, 0);
	SparseMatrix<int> sp3;
	sp3 = sp1 + sp2;
	cout << sp1 << endl;
	cout << sp2 << endl;
	cout << sp3 << endl;

}

int main()
{
	FunTest1();
	system("pause");
	return 0;
}