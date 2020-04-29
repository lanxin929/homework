/*
                                    ���м��㷨
��Ŀ����
һ��ʵ��Ŀ��
1������������м��㷨����ظ��
2�����ս���������Դʱ�İ�ȫ�Լ���㷨��
3���ܿ�����Դ������̲�p122ͼ3-5����

����ʵ��ԭ��
1�����м��㷨ԭΪ����ϵͳ��ƣ���ȷ�������ڷ����ֽ����ʱ�����ᷢ�������������пͻ��������������м��㷨���԰�������ϵͳ�������������ͻ��������̣����λ������Դ�����мұ�������ϵͳ����
2��Ϊʵ�����м��㷨��ÿ�����̱������������Լ���Ҫ��ÿ����Դ���͵������Ŀ��������������Դʱ��ϵͳ����ȷ���ý�����ӵ�е���Դ�����������������������Դ����ͬʱȷ����Դ��������������ǰ������Դ�����������������ִ�а�ȫ�Լ���㷨��
3����ȫ�Լ���㷨���ڼ��ϵͳ������Դ������Ƿ�ȫ������ȫ��ϵͳ�ſ�ִ�д˴η��䣬����ִ�д˴η��䡣
4����ȫ�Լ���㷨����ϵͳ�Է�����Դ���㷨�����н����б���Ѱ�ҳ�һ����ִ�н��̣����ոý���ռ�õ���Դ����Ѱ����һ����ִ�н��̡���ĳ��ִ��˳���ܹ�ʹ�����н���������ִ�У������һ����ȫִ�����У�������˴���Դ���䡣�������޷�ȫ��ִ�У��޷��ҵ�һ����ȫ���У����򱾴���Դ���佫����ϵͳ���벻��ȫ״̬���ʱ�����Դ����ʧ�ܡ�

����ʵ��Ҫ��
1����C++���Ա�д����ʵ�����м��㷨��
2��main ���������ִ����ѱ�д���£�ֻ�������д banker �������ύ��
3��������Դ��������½����
(1)����ɹ�
(2)����ʧ�ܣ���Ϊͬ������ᵼ��ϵͳ���벻��ȫ״̬
(3)����ʧ�ܣ�����ԭ�򡣱��磺ͬ�����뽫���¸ý��̻�õ���Դ�����������Ƶ������Դ��������ϵͳ������Դ�������������룬�������߼���֮��

��(1)�ֽ�������0
��(2)�ֽ�������1
��(3)�ֽ�������2

4��ͬһ��״̬��������������������ԣ�ÿ�ζ��ǻ��ڸ�״̬���룬�����ǻ���ǰһ�εĽ��״̬���롣�ԡ��������롱��˵��6����Դ���붼���ڳ�ʼ״̬������ģ��������Ϊ�Գ�ʼ״̬�ֱ�����6��������ԣ������ǵ�2���ڵ�1������Ľ���Ͻ��С�
*/
#include <iostream>
#include <vector>
using namespace std;

void banker(vector<int> &R, vector<vector<int> > &A, vector<vector<int> > &C, vector<vector<int> > &reqestSequence);

int main()
{
    int n, m; // ϵͳ���� n �����̡�m �ֲ�ͬ���͵���Դ
    int N; // ����������Դ�Ĵ���
    int i, j;

    cin >> n; // �����������
    cin >> m; // ������Դ������

    vector<int> R(m); // R ������ʾϵͳ��ÿ����Դ�ĵ�����

    for (i = 0; i < m; i++) // �� m ����Դ������ÿ����Դ�����������浽���� R ��
    {
        cin >> R[i];
    }

    vector<vector<int> > C(n, vector<int>(m)); // C Ϊ Claim ���󣬼����������󣬽̲��ϳ� Max ����
    for (i = 0; i < n; i++) // ���� C ����
    {
        for (j = 0; j < m; j++)
        {
            cin >> C[i][j];
        }
    }

    vector<vector<int> > A(n, vector<int>(m)); // A Ϊ Allocation ���󣬼��������
    for (i = 0; i < n; i++) // ���� A ����
    {
        for (j = 0; j < m; j++)
        {
            cin >> A[i][j];
        }
    }

////////////////////////////////////////////////////////////////////////////////
// ����Ե�ǰ״̬�� N ����Դ������ԣ�������һ�������� N ����Դ����ÿ����Դ��
// ����Ҫ���� m+1 ���������� 0 ��������ʾ������Դ�Ľ��̺ţ�ȡֵ��Χ��0 �� n-1��;
// �� 1 �� m �������ֱ��ʾ��ǰ״̬�£��ý��̶� m ����Դ������������
    cin >> N; // �������������Դ�Ĵ���

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