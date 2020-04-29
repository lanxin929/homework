/*
                                  ������δʹ��ҳ���û��㷨ģ��
��Ŀ����
һ��ʵ��Ŀ��
1���������������δʹ��ҳ���û��㷨����ظ��
2����������ҳ���û��㷨���û�ͼ���̲�p176ͼ5-5����
3�������ȱҳ�ʡ�

����ʵ��ԭ��
1�����̵�ҳ����Ŀ����Զ���ڲ���ϵͳ������ý��̵�ҳ������飩��Ŀ����ˣ�����ֻ�в���ҳ���ܹ�װ��ҳ���С�
2�������̵��� 1 ��ҳ��ʱ���п��ܳ��ָ�ҳ�治��ҳ���У������Ҫһ���㷨������̭��һ��ҳ���е�ҳ�棬�Լ����µ��õ�ҳ�浽��ҳ���С�
3��������δʹ��ҳ���û��㷨��̭ҳ�����ʱ��û��ʹ�õ�ҳ�档

����ʵ��Ҫ��
1����C++���Ա�д����ģ��������δʹ��ҳ���û��㷨��
2��main ���������ִ����ѱ�д���£�ֻ�������д lru �������ύ��
3���� lru �����У�ʵ�֣�ÿ�η���ҳ��ʱ����ҳ���ŵĴ������ҳ���е�ҳ���ţ����㲢���ȱҳ�ʡ�
4�����������ʽ������������������������������У������һ��֮�⣬ÿһ������ҳ���ŵĴ������ҳ���е�ҳ���ţ������δ����ҳ�浽ҳ�������-1�����һ����ȱҳ�ʣ�������λ��Ч���֡�*/

#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

////////////////////////////////////////////////////////////////////////////////
// lru ��������
// �������������
//   pageframeNum������ϵͳ�����ĳ���̵�ҳ����Ŀ��
//   pageCallSequence��ҳ��������У������е�ÿһ���Ǳ�����ҳ���ҳ��š�
////////////////////////////////////////////////////////////////////////////////


void lru(int pageframeNum, vector<int> &pageCallSequence);

int main()
{
    int i, pageframeNum, n;

    cin>>pageframeNum; // ��������ĳ���̵�ҳ����Ŀ(�̲��ϳơ�ҳ��Ϊ�������)
    cin>>n; // ����ý��̵�ҳ��������еĳ���
    vector<int> pageCallSequence(n); // ����ҳ��������У������е�ÿһ���Ǳ�����ҳ���ҳ���
    for(i = 0; i < n; i++) // ���� n ��ҳ��ţ�����ҳ���������
    {
        cin>>pageCallSequence[i];
    }

    lru(pageframeNum, pageCallSequence); // ģ��������δʹ��ҳ���û��㷨

    return 0;
}

//˼·1
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

//˼·2
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