#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct ListNode {
	int val;
	struct ListNode *next;
};

// 初始化链表
static struct ListNode *list_init(int val)
{
	struct ListNode *node = malloc(sizeof(struct ListNode));
	if (node) {
		node->val = val;
		node->next = NULL;
	}
	return node;
}

// 插入节点
static bool insert(struct ListNode *head, int val)
{
	while (head->next) {
		head = head->next;
	}
	struct ListNode *node = malloc(sizeof(struct ListNode));
	if (!node)
		return false;
	node->val = val;
	node->next = NULL;
	head->next = node;
	return true;
}

// 释放链表
static void destroy_list(struct ListNode *head)
{
	struct ListNode *temp;
	while (head) {
		temp = head;
		head = head->next;
		free(temp);
	}
}

// 打印链表
static void print_list(struct ListNode *head)
{
	while (head) {
		printf("%d", head->val);
		head = head->next;
	}
	printf("\n");
}

/*
给你两个 非空 的链表，表示两个非负的整数。它们每位数字都是按照 逆序 的方式存储的，并且每个节点只能存储 一位 数字。

请你将两个数相加，并以相同形式返回一个表示和的链表。

你可以假设除了数字 0 之外，这两个数都不会以 0 开头。
*/
struct ListNode *addTwoNumbers(struct ListNode *l1, struct ListNode *l2)
{
	struct ListNode *dummy_head = malloc(sizeof(struct ListNode));
	struct ListNode *current = dummy_head;
	int carry = 0; // 进位

	while (l1 || l2 || carry) {
		int sum = carry;

		if (l1) {
			sum += l1->val;
			l1 = l1->next;
		}

		if (l2) {
			sum += l2->val;
			l2 = l2->next;
		}

		carry = sum / 10;								 // 进位
		current->next = malloc(sizeof(struct ListNode)); // 新节点
		current = current->next;
		current->val = sum % 10;
		current->next = NULL;
	}

	struct ListNode *result = dummy_head->next;
	free(dummy_head);
	return result;
}

int main(void)
{
	struct ListNode *l1 = list_init(9);
	insert(l1, 9);
	insert(l1, 9);
	insert(l1, 9);
	insert(l1, 9);
	insert(l1, 9);
	print_list(l1);

	struct ListNode *l2 = list_init(9);
	insert(l2, 9);
	insert(l2, 9);
	insert(l2, 9);
	print_list(l2);

	struct ListNode *sum_list = addTwoNumbers(l1, l2);
	print_list(sum_list);

	destroy_list(l1);
	destroy_list(l2);
	destroy_list(sum_list);

	return 0;
}
