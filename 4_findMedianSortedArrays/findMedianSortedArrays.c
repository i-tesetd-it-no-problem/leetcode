#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

/*
给定两个大小分别为 m 和 n 的正序（从小到大）数组 nums1 和 nums2。请你找出并返回这两个正序数组的 中位数 。

算法的时间复杂度应该为 O(log (m+n)) 。
*/

// #define USE_O_M_N
#define USE_O_LOG_M_N

#if !defined(USE_O_M_N) && !defined(USE_O_LOG_M_N)
#error "Please choose one algorithm"
#endif

#ifdef USE_O_M_N
// 时间复杂度 O(m+n)
double findMedianSortedArrays(int *nums1, int nums1Size, int *nums2, int nums2Size)
{
	if (nums1Size == 0 && nums2Size == 0)
		return 0.0;

	int mid_index = (nums1Size + nums2Size) / 2; // 中位数的索引位置
	int dest_num = 0;
	int pre_num = 0; // 用于存储前一个数值
	int i = 0;

	int idx1 = 0, idx2 = 0;

	// 遍历到中位数位置
	while (i <= mid_index) {
		int tmp1 = (idx1 < nums1Size) ? nums1[idx1] : INT_MAX;
		int tmp2 = (idx2 < nums2Size) ? nums2[idx2] : INT_MAX;

		if (tmp1 <= tmp2) {
			dest_num = tmp1;
			idx1++;
		} else {
			dest_num = tmp2;
			idx2++;
		}

		// 保存中位值前一个值
		if (i == mid_index - 1)
			pre_num = dest_num;

		i++;
	}

	double ret = 0.0;

	if (((nums1Size + nums2Size) & 1) == 1)
		ret = dest_num; // 奇数
	else
		ret = (double)(dest_num + pre_num) / 2.0; // 偶数

	return ret;
}

#elif defined(USE_O_LOG_M_N)

// 时间复杂度 O(log(m+n))

/*
原理 :
合并两个已排序的数组时，找到一个合适的位置将数组分成左右两部分，使得左边的元素都小于右边的元素。
中位数要么是左边部分的最大值，要么是右边部分的最小值，具体取决于数组的长度是奇数还是偶数。

数组 1 分割点 i
数组 2 分割点 j

满足:
mid = (m + n + 1) / 2
(i + j) = mid;

为了保证 nums1 和 nums2 的分割是正确的，需要确保以下两个条件：

nums1[i-1] <= nums2[j]：这意味着 nums1 的左边部分（nums1[i-1]）小于或等于 nums2 的右边部分（nums2[j]）。这保证了左边所有元素都比右边的元素小。
nums2[j-1] <= nums1[i]：这意味着 nums2 的左边部分（nums2[j-1]）小于或等于 nums1 的右边部分（nums1[i]）。这也保证了左边所有元素都比右边的元素小。

如果这两个条件都满足，说明我们已经找到了正确的分割点。

使用二分法确定 i 的值 再由公式确定 j = (m + n + 1) / 2 - i;

如果 m + n 是奇数，那么中位数就是左边部分的最大值（即 max(nums1[i-1], nums2[j-1])）
如果 m + n 是偶数，那么中位数是两个中间值的平均值：(max(nums1[i-1], nums2[j-1]) + min(nums1[i], nums2[j])) / 2

*/

#define MAX(_a, _b) ((_a) < (_b) ? (_b) : (_a))
#define MIN(_a, _b) ((_a) < (_b) ? (_a) : (_b))
double findMedianSortedArrays(int *nums1, int nums1Size, int *nums2, int nums2Size)
{
	// 保证 nums1 是较小的数组
	if (nums1Size > nums2Size) {
		int *temp = nums1;
		nums1 = nums2;
		nums2 = temp;
		int tempSize = nums1Size;
		nums1Size = nums2Size;
		nums2Size = tempSize;
	}

	int left = 0, right = nums1Size;
	int mid = (nums1Size + nums2Size + 1) / 2; // 中位数索引
	int i, j;

	while (left <= right) {
		i = left + (right - left) / 2; // 二分查找nums1 的分割点
		j = mid - i;				   // (i + j) = (m + n + 1) / 2;

		int nums1_left = (i > 0) ? nums1[i - 1] : INT_MIN;		// 数组1 左边值
		int nums1_right = (i < nums1Size) ? nums1[i] : INT_MAX; // 数组1 右边边值
		int nums2_left = (j > 0) ? nums2[j - 1] : INT_MIN;		// 数组2 左边值
		int nums2_right = (j < nums2Size) ? nums2[j] : INT_MAX; // 数组2 右边边值

		// 左边永远小于右边
		if (nums1_left <= nums2_right && nums2_left <= nums1_right) {
			if ((nums1Size + nums2Size) % 2 == 1)
				return MAX(nums1_left, nums2_left); // 奇数
			else
				return (MAX(nums1_left, nums2_left) + MIN(nums1_right, nums2_right)) / 2.0; // 偶数

		} else if (nums1_left > nums2_right) {
			// i 过大
			right = i - 1;
		} else {
			// i 过小
			left = i + 1;
		}
	}

	return 0.0;
}

#endif

int main(void)
{
	int nums1[] = { 0, 0 };
	int nums2[] = { 0, 0 };

#define COUNT_OF(_A) (sizeof(_A) / sizeof(_A[0]))

	double ret = findMedianSortedArrays(nums1, COUNT_OF(nums1), nums2, COUNT_OF(nums2));
	printf("mid value is :%f\n", ret);

	return 0;
}
