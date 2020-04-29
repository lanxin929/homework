/*
单级页表地址重定位模拟
题目描述
一、实验目的
1、 用C++语言编写程序，模拟页式地址重定位。
2、 加深理解页式地址重定位技术在多道程序设计中的作用和意义。

二、实验原理
当进程在CPU上运行时，如指令中涉及逻辑地址时，操作系统自动根据页长得到页号和页内偏移，把页内偏移拷贝到物理地址寄存器，再根据页号，查页表，得到该页在内存中的块号，把块号左移页长的位数，写到物理地址寄存器。

三、实验要求
1、逻辑地址为16位，其中高6位表示页号，低10位表示页内偏移量。
2、页表为单级页表，且已定义页表寄存器ptr如下；ptr已被初始化，且页表已经加载到地址 ptr.pageTableAddr，可在main函数中直接使用（不需要你再在代码中定义SPageTableRegister了）：
struct SPageTableRegister
{
    int* pageTableAddr;    // 页表地址
    int pageTableLen;       // 页表长度
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