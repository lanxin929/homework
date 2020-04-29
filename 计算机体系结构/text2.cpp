/*
                                  最近最久未使用页面置换算法模拟
题目描述
一、实验目的
1、加深理解最近最久未使用页面置换算法及相关概念。
2、掌握描述页面置换算法的置换图（教材p176图5-5）。
3、会计算缺页率。

二、实验原理
1、进程的页面数目往往远大于操作系统分配给该进程的页框（物理块）数目，因此，往往只有部分页面能够装入页框中。
2、当进程调用 1 个页面时，有可能出现该页面不在页框中，这就需要一种算法决定淘汰哪一个页框中的页面，以加载新调用的页面到该页框中。
3、最近最久未使用页面置换算法淘汰页框中最长时间没有使用的页面。

三、实验要求
1、用C++语言编写程序，模拟最近最久未使用页面置换算法。
2、main 函数及部分代码已编写如下，只需由你编写 lru 函数并提交。
3、在 lru 函数中，实现：每次访问页面时，依页框编号的次序输出页框中的页面编号；计算并输出缺页率。
4、输入输出格式见样例输入和样例输出。在样例输出中：除最后一行之外，每一行是依页框编号的次序输出页框中的页面编号，如果尚未加载页面到页框，则输出-1；最后一行是缺页率，保留三位有效数字。*/

#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

////////////////////////////////////////////////////////////////////////////////
// lru 函数声明
// 输入参数描述：
//   pageframeNum：操作系统分配给某进程的页框数目；
//   pageCallSequence：页面调用序列，序列中的每一项是被调用页面的页面号。
////////////////////////////////////////////////////////////////////////////////


void lru(int pageframeNum, vector<int> &pageCallSequence);

int main()
{
    int i, pageframeNum, n;

    cin>>pageframeNum; // 输入分配给某进程的页框数目(教材上称“页框”为：物理块)
    cin>>n; // 输入该进程的页面调用序列的长度
    vector<int> pageCallSequence(n); // 定义页面调用序列，序列中的每一项是被调用页面的页面号
    for(i = 0; i < n; i++) // 输入 n 个页面号，构建页面调用序列
    {
        cin>>pageCallSequence[i];
    }

    lru(pageframeNum, pageCallSequence); // 模拟最近最久未使用页面置换算法

    return 0;
}

//思路1
void lru(int pageframeNum, vector<int>& pageCallSequence)
{
	int miss = 0, ms = 0, * page = new int[pageframeNum], * page_t = new int[pageframeNum]();
	for (int i = 0; i < pageframeNum; ++i)
		page[i] = -1;
	for (int page_No : pageCallSequence) {
		bool flag = false;
		for (int i = 0; i < pageframeNum; i++) {
			if (page_No == page[i]) {
				--miss;
				ms = i;
				flag = true;
			}
			++page_t[i];
			if (!flag)
				ms = page_t[i] > page_t[ms] ? i : ms;
		}
		++miss;
		page[ms] = page_No;
		page_t[ms] = 0;

		cout << page[0];
		for (int i = 1; i < pageframeNum; i++)
			cout << ',' << page[i];
		cout << endl;
	}
	printf("%.3f", (miss / (float)pageCallSequence.size()));
	delete[] page, page_t;
}

//思路2
#include<deque>
void lru2(int pageframeNum, vector<int>& pageCallSequence)
{
	int miss = 0, site;
	bool flag;
	int* page = new int[pageframeNum];
	for (int i = 0; i < pageframeNum; i++) page[i] = -1;
	deque<int> page_t;
	for (int page_No : pageCallSequence) {
		flag = false;
		for (int i = 0; i < pageframeNum; i++) {
			if (i == page_t.size()) break;
			if (page_No == page_t[i]) {
				page_t.erase(page_t.begin() + i);
				page_t.push_back(page_No);
				flag = true;
				break;
			}
			if (page_t.front() == page[i]) site = i;
		}
		if (!flag) {
			++miss;
			if (page_t.size() == pageframeNum) {
				page_t.pop_front();
				page[site] = page_No;
			}
			else
				page[page_t.size()] = page_No;
			page_t.push_back(page_No);
		}
		cout << page[0];
		for (int i = 1; i < pageframeNum; i++)
			cout << ',' << page[i];
		cout << endl;
	}
	printf("%.3f", (miss / (float)pageCallSequence.size()));
	delete[]page;
}