#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

/*
给你一个长度为 n 的整数数组 nums 和 一个目标值 target。请你从 nums 中选出三个整数，使它们的和与 target 最接近。

返回这三个数的和。

假定每组输入只存在恰好一个解。

 

示例 1：

输入：nums = [-1,2,1,-4], target = 1
输出：2
解释：与 target 最接近的和是 2 (-1 + 2 + 1 = 2)。
示例 2：

输入：nums = [0,0,0], target = 1
输出：0
解释：与 target 最接近的和是 0（0 + 0 + 0 = 0）。
 

提示：

3 <= nums.length <= 1000
-1000 <= nums[i] <= 1000
-104 <= target <= 104
*/

int compare(const void *a, const void *b)
{
	return (*(int *)a - *(int *)b);
}

int threeSumClosest(int *nums, int numsSize, int target)
{
	if (numsSize < 3)
		return INT_MAX;

	// 排序
	qsort(nums, numsSize, sizeof(int), compare);

	int closestSum = nums[0] + nums[1] + nums[2]; // 初始化为前三个数之和
	for (int i = 0; i < numsSize - 2; i++) {
		int left = i + 1, right = numsSize - 1;

		while (left < right) {
			int sum = nums[i] + nums[left] + nums[right];
			if (abs(sum - target) < abs(closestSum - target)) 
				closestSum = sum; // 更新最接近目标的和

			if (sum < target)
				left++; // 偏小，增加左指针
			else if (sum > target)
				right--; // 偏大，减小右指针
			else
				return sum; // 刚好相等
		}
	}

	return closestSum;
}

int main()
{
	int num_array[] = { -1, 2, 1, -4 };
	int ret = threeSumClosest(num_array, sizeof(num_array) / sizeof(num_array[0]), 1);
	printf("%d\n", ret); // 输出 2
	return 0;
}
