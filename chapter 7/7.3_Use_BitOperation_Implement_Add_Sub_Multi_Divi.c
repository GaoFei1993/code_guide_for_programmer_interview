/*
题目：
	只用位运算不用算术运算实现整数的加减乘除运算。
	如果给定的a和b执行加减乘除的某些结果本来就会溢出，
	那么你的函数不必对那些结果负责。

分析：
（1）加法：
若不考虑进位的加法，则a^b，相加值为所有位相加的值（没有进位）；
若只考虑进位的加法，则a&b<<1,产生值含1的位就是进位;
将进位的值加到之前的相加值上，再看有没有进位，
反复操作，直至进位为0，即相加值不产生进位，此时的值为所求值。
（2）减法：
减法a-b，等于a+(-b)。故只需要得到b的相反值。
得到b的相反值即将其全部取反(包括符号位)，再加1。
（3）乘法：
a*b = a*2^0*b0 + a*2^1*b1 +,,,+ a*2^31*b31;
其中，bi为b的二进制中第i位的值，为0或1。
（4）除法：
乘法的逆运算，b*res=a;
b*res = b*2^0*res0 + b*2^1*res1 +,,,+ b*2^31*res31 = a;
若b左移i位之后，大于a，则resi=0；
若b左移i位之后，小于等于a，则resi=1；
直至b左移0位为止，此时，若a=b,则res0=1；
                        若a>b,则res0=1，a-b为余数；
						若a<b,则res0=0，a为余数。
当然，以上只适当于a和b都不是负数的情况。
若a和b有一个或者都是负数的情况，先把a和b转为正数，计算完成后再看res的真实符号。
对于特殊情况，a为最小值，b不是最小值时，此时，a是33位的，无法表示。
故采用，c=(a+1)/b；res=(a-(c*b))/b;result=res+c;

测试案例：
（1）正常情况：
	a = 10; b = 5;
	a = 10; b = 4;
	a = 10; b = -5;
	a = -10; b = 5;
	a = 5; b = 10;
	a = 5; b = -10;
	a = -5; b = -10;
	a = -10; b = -5;
（2）不正常情况：
	b = 0;
（3）边界情况：（仅用来检测除法，乘法会超出边界，没有做处理）
	a = INT_MIN; b = INT_MIN;
	a = INT_MIN;
	b = INT_MIN;
*/
#include <stdio.h>
#define INT_MAX	2147483647
#define INT_MIN	(-INT_MAX-1)

/*加法*/
int add(int a, int b);
/*减法*/
int sub(int a, int b);
/*求相反数*/
int opposite_num(int a);
/*乘法*/
int multi(int a, int b);
/*完整除法*/
int divi(int a, int b);
/*除法辅助函数*/
int divFun(int a, int b);
/*判断是否为负*/
bool is_neg_num(int n);

int main()
{
	int a, b;
	int result_add, result_sub, result_multi, result_divi;
	
	a = -10; b = -5;

	result_add = add(a, b);
	printf("a+b=%d\n",result_add);

	result_sub = sub(a, b);
	printf("a-b=%d\n", result_sub);

	result_multi = multi(a, b);
	printf("a*b=%d\n", result_multi);

	result_divi = divi(a, b);
	printf("a/b=%d\n", result_divi);
	
	return 0;
}

/*加法*/
int add(int a, int b)
{
	int sum = a;
	while (b)
	{
		sum = a ^ b;
		b = (a&b) << 1;
		a = sum;
	}
	return sum;
}


/*减法*/
int sub(int a, int b)
{
	return add(a, opposite_num(b));
}

/*求相反数*/
int opposite_num(int a)
{
	return add(~a, 1);
}


/*乘法*/
int multi(int a, int b)
{
	int res = 0;
	int x = is_neg_num(a) ? opposite_num(a) : a;
	int y = is_neg_num(b) ? opposite_num(b) : b;

	while (y != 0)
	{
		if ((y & 1) != 0)
		{
			res = add(res, x);
		}
		x <<= 1;
		y >>= 1;
	}

	return is_neg_num(a) ^ is_neg_num(b) ? opposite_num(res) : res;
}


/*完整除法*/
int divi(int a, int b)
{
	int res;
	if (0 == b)
	{
		printf("divisor is 0!\n");
		return -1;
	}
	if (a == INT_MIN && b == INT_MIN)
		return 1;
	else if (b == INT_MIN)
		return 0;
	else if (a == INT_MIN)
	{
		res = divFun(add(a, 1), b);
		return add(res, divFun(multi(a, multi(res, b)), b));
	}
	else
		return divFun(a, b);
}

/*除法辅助函数*/
int divFun(int a, int b)
{
	int res = 0;
	int i;
	int x = is_neg_num(a) ? opposite_num(a) : a;//被除数
	int y = is_neg_num(b) ? opposite_num(b) : b;//除数

	for (i = 31; i>-1; i = sub(i, 1))
	{
		if ((x >> i) >= y)
		{
			res |= (1 << i);
			x = sub(x, y << i);
		}//if
	}//for

	return is_neg_num(a) ^ is_neg_num(b) ? opposite_num(res) : res;
}

/*判断是否为负*/
bool is_neg_num(int n)
{
	return (n >> 31) & 1;
}
