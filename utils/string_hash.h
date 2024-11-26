#ifndef _VIRTUAL_OS_STRING_HASH_H
#define _VIRTUAL_OS_STRING_HASH_H

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

typedef enum {
	STRING_HASH_KEY_NOT_FOUND = -2, //键不存在
	STRING_HASH_POINT_ERROR,		//指针错误
	STRING_HASH_SUCCESS,			//无错误
} string_hash_error_t;

struct string_hash_node {
	char *key;
	void *private_data;
	list_item list;
};

struct string_hash_table {
	list_item *table;
	size_t table_size;
} ;

/**
 * @brief 字符串哈希表初始化
 *
 * @param string_hash_table 一个实例
 * @param table_size 哈希表大小,建议为所有需要哈希处理的键大小的2-3倍
 * @return string_hash_error_t 错误码
 */
string_hash_error_t init_string_hash_table(struct string_hash_table *string_hash_table, size_t table_size);

/**
 * @brief 字符串哈希插入
 *
 * @param string_hash_table 表实例
 * @param key 字符串
 * @param private_data 需要存储数据的指针
 * @return string_hash_error_t 错误码
 */
string_hash_error_t string_hash_insert(struct string_hash_table *string_hash_table, const char *key, void *private_data);

/**
 * @brief 字符串哈希查找
 *
 * @param string_hash_table 表实例
 * @param key 字符串
 * @param error 错误码,不考虑设为NULL
 * @return void* 返回存储的指针,自行强转
 */
void *string_hash_find(struct string_hash_table *string_hash_table, const char *key, string_hash_error_t *error);

/**
 * @brief 删除字符串哈希键
 *
 * @param string_hash_table 表实例
 * @param key 字符串
 * @return string_hash_error_t 错误码
 */
string_hash_error_t string_hash_delete(struct string_hash_table *string_hash_table, const char *key);

/**
 * @brief 获取字符串哈希表中所有的键
 *
 * @param string_hash_table 表实例
 * @param keys 输出参数，用于存储所有的键
 * @param num_keys 输出参数，用于返回键的数量
 * @return string_hash_error_t 错误码
 */
string_hash_error_t string_hash_get_all_keys(struct string_hash_table *string_hash_table, char ***keys, size_t *num_keys);

/**
 * @brief 删除字符串哈希表
 *
 * @param string_hash_table
 */
void destroy_string_hash_table(struct string_hash_table *string_hash_table);

#endif /* _VIRTUAL_OS_STRING_HASH_H */
