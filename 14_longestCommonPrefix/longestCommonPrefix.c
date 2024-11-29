#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

/*
编写一个函数来查找字符串数组中的最长公共前缀。

如果不存在公共前缀，返回空字符串 ""。

示例 1：

输入：strs = ["flower","flow","flight"]
输出："fl"
示例 2：

输入：strs = ["dog","racecar","car"]
输出：""
解释：输入不存在公共前缀。
 

提示：

1 <= strs.length <= 200
0 <= strs[i].length <= 200
strs[i] 仅由小写英文字母组成
*/

char *longestCommonPrefix(char **strs, int strsSize)
{
	if (strsSize == 0)
		return "";

	int idx = 0;
	// 最短字符串的长度
	while (1) {
		// 获取当前字符
		char tmp = strs[0][idx];
		if (tmp == '\0')
			break;

		// 比较所有字符串的当前字符
		for (int i = 1; i < strsSize; i++) {
			if (strs[i][idx] != tmp) {
				if (idx == 0)
					return "";
				goto exit_while;
			}
		}
		idx++;
	}

exit_while:
	char *ret_str = malloc(sizeof(char) * (idx + 1));
	memcpy(ret_str, strs[0], idx);
	ret_str[idx] = '\0';

	return ret_str;
}

int main()
{
	char *strs[] = {
		"flower",
		"flow",
		"flight",
	};

	char *result = longestCommonPrefix(strs, sizeof(strs) / sizeof(strs[0]));

	printf("%s\n", result);
	free(result);
	return 0;
}