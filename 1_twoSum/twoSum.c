#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/time.h>
#include "../utils/number_hash.h"

// 暴力寻找
// #define USE_TWO_FOR

// 哈希查找
#define USE_HASH

#if !defined(USE_TWO_FOR) && !defined(USE_HASH)
#error "please choose an algorithm"
#endif

#ifdef USE_TWO_FOR
/*

Time taken to find the result: 0.000004/6 seconds
[15, 54]

*/

/*
给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出 和为目标值 target  的那 两个 整数，并返回它们的数组下标。

你可以假设每种输入只会对应一个答案，并且你不能使用两次相同的元素。

你可以按任意顺序返回答案。
*/

int *twoSum(int *nums, int numsSize, int target, int *returnSize)
{
	if (nums == NULL || numsSize < 2 || returnSize == NULL)
		return NULL;

	int i = 0, j = 0;
	bool can_out = false;

	struct timeval start_time, end_time;
	gettimeofday(&start_time, NULL);

	for (i = 0; i < numsSize - 1; i++) {
		for (j = i + 1; j < numsSize; j++) {
			if (nums[i] + nums[j] == target) {
				// 计算执行时间
				gettimeofday(&end_time, NULL);
				double time_taken = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_usec - start_time.tv_usec) / 1000000.0;
				printf("Time taken to find the result: %f seconds\n", time_taken);

				int *ret = malloc(sizeof(int) * 2);
				if (!ret) {
					*returnSize = 0;
					return NULL;
				} else {
					ret[0] = i;
					ret[1] = j;
					*returnSize = 2;
					return ret;
				}
			}
		}
	}

	*returnSize = 0;
	return NULL;
}

#elif (defined USE_HASH)

/*
Time taken to find the result: 0.000002/3 seconds
[15, 54]
*/

/*
给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出 和为目标值 target  的那 两个 整数，并返回它们的数组下标。

你可以假设每种输入只会对应一个答案，并且你不能使用两次相同的元素。

你可以按任意顺序返回答案。
*/
int *twoSum(int *nums, int numsSize, int target, int *returnSize)
{
	if (nums == NULL || numsSize < 2 || returnSize == NULL)
		goto err_return;

	int i = 0;
	int remain = 0; // 两数之和的另一个值
	size_t *index_arrays = NULL;
	size_t index_array_size = 0;

	struct number_hash_table table = { 0 };
	int ret;
	ret = number_hash_init(&table, numsSize * 3); // 建议Hash表为3倍
	if (ret != 0)
		goto err_return;

	// 插入所有值
	for (i = 0; i < numsSize; i++) {
		ret = number_hash_insert(&table, nums[i], i);
		if (ret != 0)
			goto err_free_table;
	}

	struct timeval start_time, end_time;
	gettimeofday(&start_time, NULL);

	// 查找目标差值
	for (i = 0; i < numsSize; i++) {
		remain = target - nums[i];
		ret = number_hash_find(&table, remain, &index_arrays, &index_array_size);
		if (ret != 0)
			continue;

		// 计算执行时间
		gettimeofday(&end_time, NULL);
		double time_taken = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_usec - start_time.tv_usec) / 1000000.0;
		printf("Time taken to find the result: %f seconds\n", time_taken);

		// 如果找到，返回结果
		int *ret_indices = calloc(2, sizeof(int));
		if (!ret_indices)
			goto err_free_table;

		ret_indices[0] = i;
		ret_indices[1] = index_arrays[0];
		*returnSize = 2;

		// 释放临时的index数组
		free(index_arrays);

		return ret_indices;
	}

	*returnSize = 0;
	return NULL;

err_free_table:
	number_hash_destroy(&table);
	free(index_arrays);

err_return:
	*returnSize = 0;
	return NULL;
}

#endif

int main(void)
{
	int *ret = NULL;
	int ret_size = 0;

	int source[] = { 1, -1, 3, 5, 7, 2, 4, -3, 8, 0, 6, 10, -7, 9, -5, 12, -2, -4, 11, 6, 5, -6, 0, 3, -1, 7, 15, -15, 8, 10, 3, -9, 4, 14, -8, 5, 2,
		7, 6, 9, 6, 0, 1, -4, -2, 3, -5, 11, 16, 7, 5, 12, -6, 19, 21, -3, 0, 8, 11, 3, -7, -9, 13, -1, 2, 6, 9, -2, 4, 7, 8, 3, 14, -6, 10, 5, -5, 7,
		13, -8, 6, 11, 3, -9, -7, 8, 15, 1, -12, 4, 2, 6, 5, -4, -7, 13, 16, -2, 8, 6, 9, 0, 4, 7, 10, -5, -3, 14, -10, 5, 6, -11, 9, 3, -2, 0, -6,
		15, -4, 12, -7, 7, 8, 10, 5, 3, 14, 6, -13, 6, 4, -8, 11, 7, 2, -5, 0, 15, 6, -10, 9, 6, 13, -8, 2, 3, -4, 5, 14, 7, -11, -2, 8, -6, 9, 3, 10,
		-3, -7, 5, 2, -9, 16, 8, 7, 13, -5, 4 };

	// 目标值 `target`
	int target = 33;

	ret = twoSum(source, sizeof(source) / sizeof(source[0]), target, &ret_size);
	if (!ret) {
		printf("there is no result\n");
		return -1;
	}

	printf("[%d, %d]\n", ret[0], ret[1]);
	free(ret);

	return 0;
}
