#include "number_hash.h"
#include <stdlib.h>
#include <string.h>

// FNV-1a 哈希函数
static uint32_t fnv1a_hash(int value, size_t table_size)
{
	uint32_t hash = 2166136261u;
	uint8_t *bytes = (uint8_t *)&value;
	for (size_t i = 0; i < sizeof(int); ++i) {
		hash ^= bytes[i];
		hash *= 16777619;
	}
	return hash % table_size;
}

// 初始化哈希表
int number_hash_init(struct number_hash_table *hash_table, size_t table_size)
{
	if (!hash_table || table_size == 0)
		return -1;

	hash_table->table = (struct number_hash_node **)calloc(table_size, sizeof(struct number_hash_node *));
	if (!hash_table->table)
		return -1;

	hash_table->table_size = table_size;
	return 0;
}

// 插入元素
int number_hash_insert(struct number_hash_table *hash_table, int value, size_t index)
{
	if (!hash_table)
		return -1;

	uint32_t hash = fnv1a_hash(value, hash_table->table_size);
	struct number_hash_node *new_node = (struct number_hash_node *)malloc(sizeof(struct number_hash_node));
	if (!new_node)
		return -1;

	new_node->value = value;
	new_node->index = index;
	new_node->next = hash_table->table[hash];
	hash_table->table[hash] = new_node;

	return 0;
}

// 查找值对应的所有索引
int number_hash_find(struct number_hash_table *hash_table, int value, size_t **indices, size_t *count)
{
	if (!hash_table || !indices || !count)
		return -1;

	uint32_t hash = fnv1a_hash(value, hash_table->table_size);
	struct number_hash_node *node = hash_table->table[hash];
	size_t *index_array = (size_t *)malloc(sizeof(size_t) * hash_table->table_size);
	if (!index_array)
		return -1;

	*count = 0;
	while (node) {
		if (node->value == value) {
			index_array[(*count)++] = node->index;
		}
		node = node->next;
	}

	if (*count > 0) {
		*indices = index_array;
		return 0;
	} else {
		free(index_array);
		return -1;
	}
}

// 删除值
int number_hash_delete(struct number_hash_table *hash_table, int value)
{
	if (!hash_table)
		return -1;

	uint32_t hash = fnv1a_hash(value, hash_table->table_size);
	struct number_hash_node *node = hash_table->table[hash];
	struct number_hash_node *prev = NULL;

	while (node) {
		if (node->value == value) {
			if (prev) {
				prev->next = node->next;
			} else {
				hash_table->table[hash] = node->next;
			}
			free(node);
			return 0;
		}
		prev = node;
		node = node->next;
	}

	return -1;
}

// 销毁哈希表
void number_hash_destroy(struct number_hash_table *hash_table)
{
	if (!hash_table)
		return;

	for (size_t i = 0; i < hash_table->table_size; ++i) {
		struct number_hash_node *node = hash_table->table[i];
		while (node) {
			struct number_hash_node *tmp = node;
			node = node->next;
			free(tmp);
		}
	}

	free(hash_table->table);
	hash_table->table = NULL;
}
