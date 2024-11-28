#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/*

给定一个长度为 n 的整数数组 height 。有 n 条垂线，第 i 条线的两个端点是 (i, 0) 和 (i, height[i]) 。

找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。

返回容器可以储存的最大水量。

说明：你不能倾斜容器。

示例 1：


输入：[1,8,6,2,5,4,8,3,7]
输出：49 
解释：图中垂直线代表输入数组 [1,8,6,2,5,4,8,3,7]。在此情况下，容器能够容纳水（表示为蓝色部分）的最大值为 49。
示例 2：

输入：height = [1,1]
输出：1

*/

#define MIN(_a, _b) ((_a) < (_b) ? (_a) : (_b))
int maxArea(int *height, int heightSize)
{
	int left = 0;				// 左指针
	int right = heightSize - 1; // 右指针
	int square = 0;				// 面积
	int length = 0;				// 长
	int high = 0;				// 高

	while (left < right) {
		length = right - left;
		high = MIN(height[left], height[right]);
		int tmp = length * high;
		square = square < tmp ? tmp : square;

		// 移动短的可能增加 移动长的不可能增加
		if (height[left] < height[right]) 
			left++;
		else 
			right--;
	}

	return square;
}

int main()
{
	int input[] = { 1, 3, 2, 5, 25, 24, 5 };
	int max_square = maxArea(input, sizeof(input) / sizeof(input[0]));
	printf("%d\n", max_square);
	return 0;
}