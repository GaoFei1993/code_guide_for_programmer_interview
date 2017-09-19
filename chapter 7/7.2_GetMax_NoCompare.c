/*
题目：
	给定两个32位整数a和b，返回a和b中较大的。不用任何比较判断。
测试案例：
（1）正常情况:
	a = 5;b = 3;
	a = 3;b = 5;
	a = -5;b = -3;
	a = -3;b = -5;
	a = 5;b = -3;
	a = -3;b = 5;
	a = -5;b = 3;
	a = 3;b = -5;
（2）不正常情况
	无
（3）边界情况（溢出）
	a = 0x7FFFFFFF; b = 0xFFFFFFFF;
	a = 0xFFFFFFFF; b = 0x7FFFFFFF;
	
溢出：运算结果超出机器字长所能表示的数值范围
（1）同号相减不会溢出
（2）异号相加不会溢出
（3）同号相加可能溢出
（4）异号相减可能溢出

判断溢出（我们需要做减法，故只有（4）会溢出）
（1）若是同号，则不可能溢出，直接输出结果；
（2）若是异号，则哪个为正输出哪个。
*/
#include <stdio.h>

int main()
{
	int a = 5;
	int b = 3;

	int c = a - b;
	bool a_msb = ((a >> 31) & 1);
	bool b_msb = ((b >> 31) & 1);
	bool c_msb = ((c >> 31) & 1);

	bool sign = a_msb ^ b_msb;//相同为0，不同为1
	int result1 = (1-a_msb)*a + (1-b_msb)*b;
	int result2 = (1-c_msb)*a + c_msb*b;

	//符号相同返回result2
	//符号不同返回result1
	int result = sign*result1 + (1 - sign)*result2;
	printf("MAX = %d\n",result);

	return 0;
}
