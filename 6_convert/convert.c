#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
将一个给定字符串 s 根据给定的行数 numRows ，以从上往下、从左到右进行 Z 字形排列。

比如输入字符串为 "PAYPALISHIRING" 行数为 3 时，排列如下：

P   A   H   N
A P L S I I G
Y   I   R
之后，你的输出需要从左往右逐行读取，产生出一个新的字符串，比如："PAHNAPLSIIGYIR"。

请你实现这个将字符串进行指定行数变换的函数：

string convert(string s, int numRows);
 

示例 1：

输入：s = "PAYPALISHIRING", numRows = 3
输出："PAHNAPLSIIGYIR"
示例 2：
输入：s = "PAYPALISHIRING", numRows = 4
输出："PINALSIGYAHRPI"
解释：
P     I    N
A   L S  I G
Y A   H R
P     I
示例 3：

输入：s = "A", numRows = 1
输出："A"
 
*/

char *convert(char *s, int numRows)
{
	int len = strlen(s);
	// 只有一行，或者行数大于或等于字符串的长度，直接返回原字符串
	if (numRows == 1 || numRows >= len)
		return s;

	int t = 2 * numRows - 2; // 周期内字符数
	char *array = (char *)malloc(sizeof(char) * (len + 1));
	int pos = 0;

	// 遍历行
	for (int i = 0; i < numRows; i++) {
		// 遍历周期
		for (int j = 0; j + i < len; j += t) {
			array[pos++] = s[j + i]; // 每一行的第一个字符
			// 如果是在对角线上，则还有一个值
			if (i > 0 && i < numRows - 1 && j + t - i < len) {
				array[pos++] = s[j + t - i];
			}
		}
	}

	array[pos] = '\0';
	return array;
}

int main(void)
{
	char *result = convert("PAYPALISHIRING", 3);
	printf("Converted: %s\n", result);
	free(result);
	return 0;
}
