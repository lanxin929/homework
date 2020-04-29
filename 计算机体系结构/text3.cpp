/*
                                    银行家算法
题目描述
一、实验目的
1、加深理解银行家算法及相关概念。
2、掌握进程申请资源时的安全性检查算法。
3、能看懂资源分配表（教材p122图3-5）。

二、实验原理
1、银行家算法原为银行系统设计，以确保银行在发放现金贷款时，不会发生不能满足所有客户需求的情况。银行家算法可以帮助操作系统避免死锁（将客户比作进程，贷款单位比作资源，银行家比作操作系统）。
2、为实现银行家算法，每个进程必须事先声明自己需要的每种资源类型的最大数目。当进程请求资源时，系统必须确保该进程所拥有的资源数不超过它事先声明最大资源数，同时确保资源请求量不超过当前可用资源量。若两项均满足则执行安全性检查算法。
3、安全性检查算法用于检查系统进行资源分配后是否安全，若安全，系统才可执行此次分配，否则不执行此次分配。
4、安全性检查算法：在系统试分配资源后，算法从现有进程列表中寻找出一个可执行进程，回收该进程占用的资源，并寻找下一个可执行进程。若某种执行顺序能够使得所有进程能依次执行，则产生一个安全执行序列，并允许此次资源分配。若进程无法全部执行（无法找到一个安全序列），则本次资源分配将导致系统进入不安全状态，故本次资源请求失败。

三、实验要求
1、用C++语言编写程序，实现银行家算法。
2、main 函数及部分代码已编写如下，只需由你编写 banker 函数并提交。
3、申请资源会出现以下结果：
(1)申请成功
(2)申请失败，因为同意申请会导致系统进入不安全状态
(3)申请失败，其它原因。比如：同意申请将导致该进程获得的资源量大于它声称的最大资源量，或者系统可用资源不足以满足申请，或者两者兼有之。

第(1)种结果，输出0
第(2)种结果，输出1
第(3)种结果，输出2

4、同一个状态，可以做无数次申请测试，每次都是基于该状态申请，而不是基于前一次的结果状态申请。以“样例输入”来说，6次资源申请都是在初始状态下申请的，可以理解为对初始状态分别做了6次申请测试，并不是第2次在第1次申请的结果上进行。
*/
#include <iostream>
#include <vector>
using namespace std;

void banker(vector<int> &R, vector<vector<int> > &A, vector<vector<int> > &C, vector<vector<int> > &reqestSequence);

int main()
{
    int n, m; // 系统中有 n 个进程、m 种不同类型的资源
    int N; // 进程请求资源的次数
    int i, j;

    cin >> n; // 输入进程数量
    cin >> m; // 输入资源类型数

    vector<int> R(m); // R 向量表示系统中每种资源的的总量

    for (i = 0; i < m; i++) // 对 m 种资源，输入每种资源的总量，保存到向量 R 中
    {
        cin >> R[i];
    }

    vector<vector<int> > C(n, vector<int>(m)); // C 为 Claim 矩阵，即最大需求矩阵，教材上称 Max 矩阵
    for (i = 0; i < n; i++) // 输入 C 矩阵
    {
        for (j = 0; j < m; j++)
        {
            cin >> C[i][j];
        }
    }

    vector<vector<int> > A(n, vector<int>(m)); // A 为 Allocation 矩阵，即分配矩阵
    for (i = 0; i < n; i++) // 输入 A 矩阵
    {
        for (j = 0; j < m; j++)
        {
            cin >> A[i][j];
        }
    }

////////////////////////////////////////////////////////////////////////////////
// 欲针对当前状态做 N 次资源请求测试，故这里一次性输入 N 次资源请求，每次资源请
// 求需要输入 m+1 个整数：第 0 个整数表示申请资源的进程号（取值范围：0 至 n-1）;
// 第 1 至 m 个整数分别表示当前状态下，该进程对 m 种资源的申请数量。
    cin >> N; // 输入进程请求资源的次数

    vector<vector<int> > reqestSequence(N, vector<int>(m+1));
    for (i = 0; i < N; i++)
    {
        for (j = 0; j <= m; j++)
        {
            cin >> reqestSequence[i][j];
        }
    }
//
////////////////////////////////////////////////////////////////////////////////
    banker(R, A, C, reqestSequence);

    return 0;
}

bool compare(vector<int>& left, vector<int>& right)
{
	for (int i = 0; i < left.size(); i++)
		if (left[i] > right[i])
			return false;
	return true;
}
void security_algorithm(vector<int> Av, vector<vector<int> > Al, vector<vector<int> > Ne, vector<int>& req, int P, vector<int>& Ma)
{
	vector<bool> Fi(Al.size());
	for (int i = 0; i < Al.size(); i++)
		Fi[i] = false;
	vector<int> sq;
	for (int j = 0; j < Av.size(); j++) {
		Av[j] -= req[j];
		Al[P][j] += req[j];
		Ne[P][j] -= req[j];
	}
	bool flag = true;
	for (int k = 0; k < Av.size(); k++)
		if (Ne[P][k] > 0)
			flag = false;
	if (flag)
	{
		for (int k = 0; k < Av.size(); k++)
			Av[k] += Al[P][k];
		Fi[P] = true;
		P = 1;
	}
	else P = 0;
	for (P; P < Al.size(); P++) {
		flag = false;
		for (int p = 0; p < Al.size(); p++) {
			if (Fi[p] || !compare(Ne[p], Av)) continue;
			for (int j = 0; j < Av.size(); j++)
				Av[j] += Al[p][j];
			sq.push_back(p);
			flag = true; Fi[p] = true;
			break;
		}
		if (!flag) {
			cout << 1 << endl;
			return;
		}
	}
	cout << 0 << '\n' << sq[0];
	for (int i = 1; i < sq.size(); i++)
		cout << ',' << sq[i];
	cout << endl;
}
void banker(vector<int>& R, vector<vector<int> >& A, vector<vector<int> >& C, vector<vector<int> >& req)
{
	vector<vector<int> > Need(A.size(), vector<int>(R.size()));
	for (int i = 0; i < A.size(); i++) {
		for (int j = 0; j < R.size(); j++) {
			Need[i][j] = C[i][j] - A[i][j];
			R[j] -= A[i][j];
		}
	}
	for (int s = 0; s < req.size(); s++) {
		int P = req[s][0];
		req[s].erase(req[s].begin());
		if (compare(req[s], Need[P]) && compare(req[s], R))
			security_algorithm(R, A, Need, req[s], P, C[P]);
		else
			cout << 2 << endl;
	}
}