#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/*
给定两个大小分别为 m 和 n 的正序（从小到大）数组 nums1 和 nums2。请你找出并返回这两个正序数组的 中位数 。

算法的时间复杂度应该为 O(log (m+n)) 。
*/

#define COUNT_OF(_A) (sizeof(_A) / sizeof(_A[0]))

double findMedianSortedArrays(int *nums1, int nums1Size, int *nums2, int nums2Size)
{
	if (!nums1 || !nums2)
		return 0;

	int *new_array = malloc(sizeof(int) * (nums1Size + nums2Size));
	if (new_array == NULL)
		return 0;

	int idx1 = 0, idx2 = 0;
	int tmp1 = 0, tmp2 = 0;
	size_t new_idx = 0;

	// 合并排序两个数组
	while (idx1 < nums1Size || idx2 < nums2Size) {
		tmp1 = (idx1 < nums1Size) ? nums1[idx1] : INT_MAX;
		tmp2 = (idx2 < nums2Size) ? nums2[idx2] : INT_MAX;

		if (tmp1 <= tmp2) {
			new_array[new_idx++] = tmp1;
			idx1++;
		} else {
			new_array[new_idx++] = tmp2;
			idx2++;
		}
	}

	// 奇数
	double ret = 0.0;
	if ((new_idx & 1) == 1)
		ret = new_array[(int)(new_idx / 2)];
	else
		ret = (double)(new_array[(int)(new_idx / 2)] + new_array[(int)(new_idx / 2) - 1]) / 2;

	free(new_array);
	new_array = NULL;

	return ret;
}

int main(void)
{
	int nums1[] = { 1, 2 };
	int nums2[] = { 3, 4 };

	double ret = findMedianSortedArrays(nums1, COUNT_OF(nums1), nums2, COUNT_OF(nums2));
	printf("mid value is :%f\n", ret);

	return 0;
}
