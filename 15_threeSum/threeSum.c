#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

/*
给你一个整数数组 nums ，判断是否存在三元组 [nums[i], nums[j], nums[k]] 满足 i != j、i != k 且 j != k ，同时还满足 nums[i] + nums[j] + nums[k] == 0 。请你返回所有和为 0 且不重复的三元组。

注意：答案中不可以包含重复的三元组。

 

 

示例 1：

输入：nums = [-1,0,1,2,-1,-4]
输出：[[-1,-1,2],[-1,0,1]]
解释：
nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0 。
nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0 。
nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0 。
不同的三元组是 [-1,0,1] 和 [-1,-1,2] 。
注意，输出的顺序和三元组的顺序并不重要。
示例 2：

输入：nums = [0,1,1]
输出：[]
解释：唯一可能的三元组和不为 0 。
示例 3：

输入：nums = [0,0,0]
输出：[[0,0,0]]
解释：唯一可能的三元组和为 0 。
 

提示：

3 <= nums.length <= 3000
-105 <= nums[i] <= 105
*/

int compare(const void *a, const void *b)
{
	return (*(int *)a - *(int *)b);
}

int **threeSum(int *nums, int numsSize, int *returnSize, int **returnColumnSizes)
{
	if (numsSize < 3) {
		*returnSize = 0;
		return NULL;
	}

	int i, j;

	// 排序
	qsort(nums, numsSize, sizeof(int), compare);

	// 结果数组
	int **result = malloc(sizeof(int *) * numsSize * numsSize);
	*returnColumnSizes = malloc(sizeof(int) * numsSize * numsSize);
	*returnSize = 0;

	for (i = 0; i < numsSize; i++) {
		if (i > 0 && nums[i] == nums[i - 1]) // 防止重复
			continue;

		int left = i + 1;		  // 左指针
		int right = numsSize - 1; // 右指针

		while (left < right) {
			int sum = nums[i] + nums[left] + nums[right];
			if (sum == 0) {
				// 找到一个三元组
				result[*returnSize] = malloc(sizeof(int) * 3);
				result[*returnSize][0] = nums[i];
				result[*returnSize][1] = nums[left];
				result[*returnSize][2] = nums[right];
				(*returnColumnSizes)[*returnSize] = 3;
				(*returnSize)++;

				// 跳过重复的数字
				while (left < right && nums[left] == nums[left + 1])
					left++;
				while (left < right && nums[right] == nums[right - 1])
					right--;

				left++;
				right--;
			} else if (sum < 0) {
				left++;
			} else {
				right--;
			}
		}
	}

	// 返回结果
	return result;
}

int main()
{
	int nums[] = { -1, 0, 1, 2, -1, -4 };
	int numsSize = sizeof(nums) / sizeof(nums[0]);
	int returnSize = 0;
	int *returnColumnSizes = NULL;

	int **result = threeSum(nums, numsSize, &returnSize, &returnColumnSizes);

	printf("Total: %d\n", returnSize);
	for (int i = 0; i < returnSize; i++) {
		printf("[");
		for (int j = 0; j < 3; j++) {
			printf("%d", result[i][j]);
			if (j < 2)
				printf(", ");
		}
		printf("]\n");
	}

	// 释放内存
	for (int i = 0; i < returnSize; i++) {
		free(result[i]);
	}
	free(result);
	free(returnColumnSizes);

	return 0;
}