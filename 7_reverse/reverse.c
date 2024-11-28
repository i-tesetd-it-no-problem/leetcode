#include <cstdint>
#include <stdio.h>
#include <stdint.h>

/*
给你一个 32 位的有符号整数 x ，返回将 x 中的数字部分反转后的结果。

如果反转后整数超过 32 位的有符号整数的范围 [−2^31,  2^31 − 1] ，就返回 0。

假设环境不允许存储 64 位整数（有符号或无符号）。
*/

int reverse(int x)
{
	int ret = 0;
	while (x != 0) {
		int digit = x % 10; // 取出当前末尾数字
		x /= 10;			// 去掉末尾数字

		if (ret > INT32_MAX / 10 || ret < INT32_MIN / 10)
			return 0;

		ret = ret * 10 + digit; // 更新反转

		if (ret > INT32_MAX)
			return INT32_MAX;
		else if (ret < INT32_MIN)
			return INT32_MIN;
	}

	return ret;
}

int main(void)
{
	printf("%d\n", reverse(1534236469));
	return 0;
}
