/*
����ҳ���ַ�ض�λģ��
��Ŀ����
һ��ʵ��Ŀ��
1�� ��C++���Ա�д����ģ��ҳʽ��ַ�ض�λ��
2�� �������ҳʽ��ַ�ض�λ�����ڶ����������е����ú����塣

����ʵ��ԭ��
��������CPU������ʱ����ָ�����漰�߼���ַʱ������ϵͳ�Զ�����ҳ���õ�ҳ�ź�ҳ��ƫ�ƣ���ҳ��ƫ�ƿ����������ַ�Ĵ������ٸ���ҳ�ţ���ҳ���õ���ҳ���ڴ��еĿ�ţ��ѿ������ҳ����λ����д�������ַ�Ĵ�����

����ʵ��Ҫ��
1���߼���ַΪ16λ�����и�6λ��ʾҳ�ţ���10λ��ʾҳ��ƫ������
2��ҳ��Ϊ����ҳ�����Ѷ���ҳ��Ĵ���ptr���£�ptr�ѱ���ʼ������ҳ���Ѿ����ص���ַ ptr.pageTableAddr������main������ֱ��ʹ�ã�����Ҫ�����ڴ����ж���SPageTableRegister�ˣ���
struct SPageTableRegister
{
    int* pageTableAddr;    // ҳ���ַ
    int pageTableLen;       // ҳ����
    SPageTableRegister();
} ptr;
*/

#include<iostream>
int main() {
	unsigned short logical_add;
	std::cin >> logical_add;
	short pagenum = logical_add >> 10;
	if (pagenum < ptr.pageTableLen && pagenum > -1)
		std::cout << (ptr.pageTableAddr[pagenum] << 10) + logical_add % 1024;
	else
		std::cout << 'N';
	return 0;
}