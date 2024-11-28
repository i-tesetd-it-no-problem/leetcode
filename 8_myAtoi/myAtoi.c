#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>

/*
请你来实现一个 myAtoi(string s) 函数，使其能将字符串转换成一个 32 位有符号整数。

函数 myAtoi(string s) 的算法如下：

空格：读入字符串并丢弃无用的前导空格（" "）
符号：检查下一个字符（假设还未到字符末尾）为 '-' 还是 '+'。如果两者都不存在，则假定结果为正。
转换：通过跳过前置零来读取该整数，直到遇到非数字字符或到达字符串的结尾。如果没有读取数字，则结果为0。
舍入：如果整数数超过 32 位有符号整数范围 [−2^31,  2^31 − 1] ，需要截断这个整数，使其保持在这个范围内。
具体来说，小于 −2^31 的整数应该被舍入为 −2^31 ，大于 2^31 − 1 的整数应该被舍入为 2^31 − 1 。
返回整数作为最终结果。
*/

int myAtoi(char *s)
{
	int flag = 1; // 符号位
	int ret = 0;

	// 跳过空格
	while (*s == ' ') 
		s++;

	// 处理符号
	if (*s == '-') {
		flag = -1;
		s++;
	} else if (*s == '+') {
		s++;
	}

	// 处理数字部分
	while (*s >= '0' && *s <= '9') {
		int digit = *s - '0';

		// 检查溢出
		if (ret > (INT32_MAX - digit) / 10) {
			return flag == 1 ? INT32_MAX : INT32_MIN;
		}

		ret = ret * 10 + digit;
		s++;
	}

	return ret * flag;
}

int main(void)
{
	printf("%d\n", myAtoi("-91283472332"));
	return 0;
}
