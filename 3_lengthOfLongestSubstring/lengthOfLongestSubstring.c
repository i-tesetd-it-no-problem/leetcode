#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/*
给定一个字符串 s ，请你找出其中不含有重复字符的 最长子串的长度。
*/

// 滑动窗口

#define MAX(_a, _b) ((_a) < (_b) ? (_b) : (_a))

int lengthOfLongestSubstring(char *s)
{
	if (!s)
		return 0;

	int char_hash[256]; // 记录每个字符的最新位置
	memset(char_hash, -1, sizeof(int) * 256);

	int left = 0; // 左边界
	int ret_num = 0;

	for (int right = 0; s[right] != '\0'; right++) {
		// 字符上次出现的位置
		int last_pos = char_hash[s[right]];

		// 字符出现过
		if (last_pos > -1)
			left = MAX(left, last_pos + 1); // 更新左边界到下一个

		// 更新当前字符出现的位置
		char_hash[s[right]] = right;

		// 更新窗口的大小
		ret_num = MAX(ret_num, (right - left + 1));
	}

	return ret_num;
}

int main(void)
{
	char *s = "c";
	int ret = lengthOfLongestSubstring(s);
	printf("length is :%d\n", ret);

	return 0;
}
