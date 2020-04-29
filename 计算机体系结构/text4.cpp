/*                                �༶�������е����㷨
��Ŀ����
 һ��ʵ��Ŀ��
1���������༶�������У�multilevel feedback queue�������㷨����ظ��
2������ƽ����תʱ�䡢ƽ����Ȩ��תʱ��ļ��㷽����

����ʵ��ԭ��
1������ N ���������̶��У�������0������1������������N-1�����ڴ�ž������̡�ÿ���������ȼ���ͬ���ҴӶ���0������N-1�����ȼ����εݼ���
2����ͬ�����еĽ����������ʱ��Ƭ���Ȳ�ͬ�����ȼ�Խ�ͣ�ʱ��ƬԽ�������磬����0�н��̵�ʱ��ƬΪ5������1�н��̵�ʱ��ƬΪ10�ȵȡ�
3���ڶ����ڲ�������֮����������ȷ���FCFS���㷨����ʱ��Ƭ��ʱ���ƽ��е��ȣ�λ�ڶ���ͷ���Ľ��̣����׽��̣���ִ�У������ʱ��Ƭ��ʱ�ڣ���ִ�н�������ӱ��������Ƴ��������ʱ��Ƭ��δ�����н���������������һ������ĩβ��������������������ȼ����У������뱾������ĩβ����Ȼ������ǰ�����¶��и��������µ�ʱ��Ƭ��
4�������̵����ڴ�󣬽������0ĩβ���������������0�涨��ʱ��Ƭ��
5������ִ�и����ȼ������еĶ��׽��̣��������ȼ�������û�о������̣���ִ����һ�����ȼ������еĶ��׽��̡�
6������ִ�е����ȼ������еĶ��׽���ʱ�����µĽ��̵�������ȼ����У��������жϵ����ȼ����̣����л��������ȼ�����ִ�У��������Σ��̲�p104�Ĵ������ǣ��������ȼ������еĶ��׽����Ƶ�����β�����˴������ý̲��еĴ����������ǣ����ֵ����ȼ�������Ȼλ�����ڶ����ײ�����Ҫ�����Ƶ�����β������
7�����׿�������ϵͳֻ��1�����У���༶�������е����㷨���˻���ʱ��Ƭ��ת�����㷨��
8�����׿�������ǰ����ִ�еĽ���ֻ����ĳ���еĶ��׽��̡�

����ʵ��Ҫ��
1����C++���Ա�д����ʵ�ֶ༶�������е����㷨��
2�����������ͬʱ���Լ��������������Ⱥ�˳��ʼִ�У��������2��3ͬʱ�����������������ݵ�ʱ����������ǽ���2���ʽ���2�ڽ���֮ǰ��ʼִ�С�
3����ϵͳ��ֻ��1�����У�������0ʱ��������½��̵������0�����ͬʱ������0�Ķ��׽�������ʱ��Ƭ���굫����ʱ����δ���꣬��Լ���Ƚ����׽����Ƶ�����0β�����ٽ��½��̲������0β����
4�������ƽ����תʱ�䡢��Ȩƽ����תʱ�䱣��3λ��Ч���֡�
5��main ���������ִ����ѱ�д���£�ֻ�������д mfqSchedule �������ύ��
*/
#include <iostream>
#include <vector>
using namespace std;

struct SPCB
{
    int pid; // ���̺�
    int arrivalTime; // ����ʱ��
    int workTime; // ����ʱ��
    int remainingTime; // ʣ�����ʱ��
    int timeSlice; // ʣ��ʱ��Ƭ
    int startTime; // ��ʼʱ�䡣��Ҫʱ������ mfqSchedule ������ʹ�ã����ڼ�¼���̿�ʼִ�е�ʱ��
    int endTime; // ������ɷ����ʱ�䡣��Ҫʱ������ mfqSchedule ������ʹ�ã����ڼ�¼������ɷ����ʱ��
};

void mfqSchedule(vector<SPCB> &pcb, const vector<int> &timeSlice);

int main()
{
    int m, n; // m Ϊ����������n Ϊ��������
    int i;

    cin >> m >> n; // ������������ͽ�������
    vector<int> timeSlice(m); // t Ϊ�������飬��� m �����е�ʱ��Ƭ����
    vector<SPCB> pcb(n);

    for (i = 0; i < m; i++)
    {
        cin >> timeSlice[i]; // ���� m �����е�ʱ��Ƭ���ȣ�һ����˵����һ�����е�ʱ��Ƭ���ȴ���ǰһ�������磬��һ��ʱ��Ƭ������ǰһ���� 2 ��
    }

    for (i = 0; i < n; i++)
    {
        cin >> pcb[i].arrivalTime; // ����� i �����̵ĵ���ʱ��
        cin >> pcb[i].workTime; // ����� i �����̵ķ���ʱ��

        pcb[i].pid = i; // �� i �����̵Ľ��̺�ȡΪ i
        pcb[i].remainingTime = pcb[i].workTime; // ʣ�����ʱ���ʼ��Ϊ����ʱ��
        pcb[i].timeSlice = timeSlice[0]; // ʣ��ʱ��Ƭ��ʼ��Ϊ������ȼ����е�ʱ��Ƭ����
        pcb[i].startTime = -1; // ��ʼʱ���ʼ��Ϊ -1����ʾ��ʱ��ʼʱ���¼����Чֵ
    }

    mfqSchedule(pcb, timeSlice);

    return 0;
}

#include<deque>
#include <iomanip>
void implement(vector<SPCB>& pcb, vector<deque<int> >& deqs, const vector<int>& timeSlice, int t, int p)
{
	if (deqs[p].empty()) return;
	int P = deqs[p][0];//pcb���±�
	--pcb[P].remainingTime;
	--pcb[P].timeSlice;
	if (pcb[P].remainingTime == 0) {
		pcb[P].endTime = t;
		deqs[p].pop_front();
	}
	else {
		if (pcb[P].timeSlice > 0) return;
		deqs[p].pop_front();
		if (p < deqs.size() - 1)//����������һ�� ��ָ��p�ƶ�����һ����
			++p;
		deqs[p].push_back(P);
		pcb[P].timeSlice = timeSlice[p];
	}
}
void mfqSchedule(vector<SPCB>& pcb, const vector<int>& timeSlice)
{
	vector<deque<int> > deqs(timeSlice.size());//ϵͳ ÿ��deque��һ������ �����¼pcb���±�
	int t = 0, p = 0, n = pcb.size();	//t ����ʱ�� p ����ָ��  n pcb����������Ϊ0ʱ˵��û�н��̲�����,�������ж��� 
	while (true) {
		for (int i = 0; i < deqs.size(); i++) { //ɨ��deqs 
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
		bool flag = true;//�ж��Ƿ�ȫ��ִ�����
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
