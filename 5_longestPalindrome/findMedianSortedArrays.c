#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/*
给你一个字符串 s，找到 s 中最长的 
回文
 
子串
。

 

示例 1：

输入：s = "babad"
输出："bab"
解释："aba" 同样是符合题意的答案。
示例 2：

输入：s = "cbbd"
输出："bb"
*/

char *longestPalindrome(const char *s)
{
	int n = strlen(s);
	if (n < 2) {
		// 分配内存并返回整个字符串
		char *result = (char *)malloc((n + 1) * sizeof(char));
		strcpy(result, s);
		return result;
	}

	int maxLen = 1;
	int begin = 0;

	bool dp[n][n];
	memset(dp, 0, sizeof(dp));

	// 所有长度为1的子串都是回文
	for (int i = 0; i < n; i++)
		dp[i][i] = true;

	// 长度
	for (int L = 2; L <= n; L++) {
		// 左边界
		for (int j = 0; j <= n - L; j++) {
			int k = j + L - 1; // 右边界

			if (s[j] == s[k]) {
				if (L == 2)
					dp[j][k] = true; // 子串长度为2，且字符相同
				else
					dp[j][k] = dp[j + 1][k - 1]; // 依赖内部子串
			} else
				dp[j][k] = false;

			// 更新最大长度和起始位置
			if (dp[j][k] && L > maxLen) {
				maxLen = L;
				begin = j;
			}
		}
	}

	char *longestPal = (char *)malloc((maxLen + 1) * sizeof(char));
	if (!longestPal)
		return NULL;

	// 复制最长回文子串并添加字符串结束符
	strncpy(longestPal, s + begin, maxLen);
	longestPal[maxLen] = '\0';

	return longestPal;
}

int main(void)
{
	const char *testStr = "abcdedcba";
	char *ret = longestPalindrome(testStr); // 调用函数

	if (ret != NULL) {
		printf("%s\n", ret);
		free(ret);
	}

	return 0;
}
