#ifndef NUMBER_HASH_H
#define NUMBER_HASH_H

#include <stdint.h>
#include <stddef.h>

// 哈希表节点结构
struct number_hash_node {
	int value;					   // 存储的值
	size_t index;				   // 对应数组中的索引
	struct number_hash_node *next; // 链表指针
};

// 哈希表结构
struct number_hash_table {
	struct number_hash_node **table; // 哈希表的数组，每个槽存放链表头指针
	size_t table_size;				 // 哈希表大小
};

/**
 * @brief 初始化哈希表
 *
 * @param hash_table 哈希表实例
 * @param table_size 哈希表大小
 * @return 0 成功，非零值失败
 */
int number_hash_init(struct number_hash_table *hash_table, size_t table_size);

/**
 * @brief 插入元素到哈希表
 *
 * @param hash_table 哈希表实例
 * @param value 插入的值
 * @param index 元素的索引
 * @return 0 成功，非零值失败
 */
int number_hash_insert(struct number_hash_table *hash_table, int value, size_t index);

/**
 * @brief 查找值对应的所有索引
 *
 * @param hash_table 哈希表实例
 * @param value 查找的值
 * @param indices 输出参数，存储找到的索引数组
 * @param count 输出参数，存储找到的索引数量
 * @return 0 成功，非零值失败
 */
int number_hash_find(struct number_hash_table *hash_table, int value, size_t **indices, size_t *count);

/**
 * @brief 删除哈希表中的值
 *
 * @param hash_table 哈希表实例
 * @param value 删除的值
 * @return 0 成功，非零值失败
 */
int number_hash_delete(struct number_hash_table *hash_table, int value);

/**
 * @brief 销毁哈希表，释放内存
 *
 * @param hash_table 哈希表实例
 */
void number_hash_destroy(struct number_hash_table *hash_table);

#endif /* NUMBER_HASH_H */
