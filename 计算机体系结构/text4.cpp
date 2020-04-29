/*                                多级反馈队列调度算法
题目描述
 一、实验目的
1、加深理解多级反馈队列（multilevel feedback queue）调度算法及相关概念。
2、掌握平均周转时间、平均带权周转时间的计算方法。

二、实验原理
1、设置 N 个就绪进程队列，即队列0，队列1，……，队列N-1，用于存放就绪进程。每个队列优先级不同，且从队列0到队列N-1，优先级依次递减。
2、不同队列中的进程所赋予的时间片长度不同；优先级越低，时间片越长，比如，队列0中进程的时间片为5，队列1中进程的时间片为10等等。
3、在队列内部，进程之间采用先来先服务（FCFS）算法辅以时间片限时机制进行调度：位于队列头部的进程（队首进程）先执行，如果在时间片限时内，它执行结束，则从本级队列移除；如果它时间片内未能运行结束，则将它移入下一级队列末尾（若本级队列是最低优先级队列，则移入本级队列末尾），然后按它当前所在新队列给它分配新的时间片。
4、当进程到达内存后，进入队列0末尾，并给它分配队列0规定的时间片。
5、优先执行高优先级队列中的队首进程，若高优先级队列中没有就绪进程，则执行下一级优先级队列中的队首进程。
6、正在执行低优先级队列中的队首进程时，有新的进程到达高优先级队列，则立即中断低优先级进程，并切换到高优先级进程执行（此种情形，教材p104的处理方法是：将低优先级队列中的队首进程移到队列尾部。此处不采用教材中的处理方法，而是：保持低优先级进程仍然位于所在队列首部，不要将它移到队列尾部）。
7、容易看出，若系统只有1个队列，则多级反馈队列调度算法将退化成时间片轮转调度算法。
8、容易看出，当前正在执行的进程只能是某队列的队首进程。

三、实验要求
1、用C++语言编写程序，实现多级反馈队列调度算法。
2、若多个进程同时到达，约定按进程输入的先后顺序开始执行，比如进程2和3同时到达，但在输入测试数据的时候，先输入的是进程2，故进程2在进程之前开始执行。
3、当系统中只有1个队列，即队列0时，如果有新进程到达队列0，与此同时，队列0的队首进程正好时间片用完但服务时间尚未用完，则约定先将队首进程移到队列0尾部，再将新进程插入队列0尾部。
4、输出的平均周转时间、带权平均周转时间保留3位有效数字。
5、main 函数及部分代码已编写如下，只需由你编写 mfqSchedule 函数并提交。
*/
#include <iostream>
#include <vector>
using namespace std;

struct SPCB
{
    int pid; // 进程号
    int arrivalTime; // 到达时间
    int workTime; // 服务时间
    int remainingTime; // 剩余服务时间
    int timeSlice; // 剩余时间片
    int startTime; // 开始时间。必要时，可在 mfqSchedule 函数中使用，用于记录进程开始执行的时间
    int endTime; // 进程完成服务的时间。必要时，可在 mfqSchedule 函数中使用，用于记录进程完成服务的时间
};

void mfqSchedule(vector<SPCB> &pcb, const vector<int> &timeSlice);

int main()
{
    int m, n; // m 为队列数量，n 为进程数量
    int i;

    cin >> m >> n; // 输入队列数量和进程数量
    vector<int> timeSlice(m); // t 为整型数组，存放 m 级队列的时间片长度
    vector<SPCB> pcb(n);

    for (i = 0; i < m; i++)
    {
        cin >> timeSlice[i]; // 输入 m 级队列的时间片长度；一般来说，后一级队列的时间片长度大于前一级，比如，后一级时间片长度是前一级的 2 倍
    }

    for (i = 0; i < n; i++)
    {
        cin >> pcb[i].arrivalTime; // 输入第 i 个进程的到达时间
        cin >> pcb[i].workTime; // 输入第 i 个进程的服务时间

        pcb[i].pid = i; // 第 i 个进程的进程号取为 i
        pcb[i].remainingTime = pcb[i].workTime; // 剩余服务时间初始化为服务时间
        pcb[i].timeSlice = timeSlice[0]; // 剩余时间片初始化为最高优先级队列的时间片长度
        pcb[i].startTime = -1; // 开始时间初始化为 -1，表示此时开始时间记录是无效值
    }

    mfqSchedule(pcb, timeSlice);

    return 0;
}

#include<deque>
#include <iomanip>
void implement(vector<SPCB>& pcb, vector<deque<int> >& deqs, const vector<int>& timeSlice, int t, int p)
{
	if (deqs[p].empty()) return;
	int P = deqs[p][0];//pcb的下标
	--pcb[P].remainingTime;
	--pcb[P].timeSlice;
	if (pcb[P].remainingTime == 0) {
		pcb[P].endTime = t;
		deqs[p].pop_front();
	}
	else {
		if (pcb[P].timeSlice > 0) return;
		deqs[p].pop_front();
		if (p < deqs.size() - 1)//如果不是最后一列 则指针p移动到下一队列
			++p;
		deqs[p].push_back(P);
		pcb[P].timeSlice = timeSlice[p];
	}
}
void mfqSchedule(vector<SPCB>& pcb, const vector<int>& timeSlice)
{
	vector<deque<int> > deqs(timeSlice.size());//系统 每个deque是一个队列 里面记录pcb的下标
	int t = 0, p = 0, n = pcb.size();	//t 运行时间 p 队列指针  n pcb个数，当减为0时说明没有进程插入了,不用再判断了 
	while (true) {
		for (int i = 0; i < deqs.size(); i++) { //扫描deqs 
			if (!deqs[i].empty()) {
				p = i;
				break;
			}
		}
		implement(pcb, deqs, timeSlice, t, p);
		for (int i = 0; i < pcb.size(); i++) {
			if (n == 0) break;
			if (t == pcb[i].arrivalTime) {
				deqs[0].push_back(i);
				pcb[i].timeSlice = timeSlice[0];
				--n; p = 0;
			}
		}
		++t;
		bool flag = true;//判断是否全部执行完成
		for (int i = p; i < deqs.size(); i++) {
			if (!deqs[i].empty()) {
				flag = false;
				break;
			}
		}
		if (flag && n == 0) break;
	}
	double weight = 0; t = 0;
	for (int i = 0; i < pcb.size(); i++) {
		n = pcb[i].endTime - pcb[i].arrivalTime;
		t += n;
		weight += n / (double)pcb[i].workTime;
	}
	cout << fixed << setprecision(3) << (double)t / pcb.size() + 1e-8 << endl;
	cout << fixed << setprecision(3) << weight / pcb.size() + 1e-8;
}
