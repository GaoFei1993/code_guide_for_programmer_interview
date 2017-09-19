/*
题目：
	统计整数的二进制中1的个数

分析：
（1）最简单的解法：将整数不断右移，将最低位的值加起来即可。
（2）利用n&(n-1)：n&(n-1)能统计出该数是不是2的n次幂。同理，n = n&(n-1)直至n=0；
（3）平行算法：先将n写成二进制形式，然后相邻位相加，重复这个过程，直到只剩下一位。(其实我没有弄懂具体原理)
*/
#include <stdio.h>

int count_1(int n);
int count_2(int n);
int count_3(unsigned int n);

int main()
{
	int n = 255;
	int result1, result2, result3;

	result1 = count_1(n);
	printf("result1 = %d\n",result1);

	result2 = count_2(n);
	printf("result2 = %d\n", result2);
	
	result3 = count_3(n);
	printf("result3 = %d\n", result3);

	return 0;
}

int count_1(int n)
{
	int count = 0;
	while (n)
	{
		count += n & 0x1;
		n >>= 1;
	}//while

	return count;
}

int count_2(int n)
{
	int count = 0;
	while (n)
	{
		n &= (n - 1); /*每执行一次，都会抹掉最右端的1*/
		++count;
	}//while
	return count;
}

//注意输入转换为unsigned int
//写成((n >> 1) & 0x55555555)，OK
//改成(n >> 1) & 0x55555555，就会出错，没有找到原因
int count_3(unsigned int n)
{
	n = (n & 0x55555555) + ((n >> 1) & 0x55555555);
	n = (n & 0x33333333) + ((n >> 2) & 0x33333333);
	n = (n & 0x0f0f0f0f) + ((n >> 4) & 0x0f0f0f0f);
	n = (n & 0x00ff00ff) + ((n >> 8) & 0x00ff00ff);
	n = (n & 0x0000ffff) + ((n >> 16) & 0x0000ffff);
	return n;
}
