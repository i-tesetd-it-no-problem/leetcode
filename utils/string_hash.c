#include "string_hash.h"

// FNV-1a hash
static uint32_t string_hash(const char *key, size_t table_size)
{
	uint32_t hash = 2166136261u;

	while (*key) {
		hash ^= (uint8_t)*key++;
		hash *= 16777619;
	}

	return hash % table_size;
}

string_hash_error_t init_string_hash_table(struct string_hash_table *string_hash_table, size_t table_size)
{
	if (!string_hash_table || table_size == 0)
		return STRING_HASH_POINT_ERROR;

	string_hash_table->table = (list_item *)malloc(table_size * sizeof(list_item));
	if (!string_hash_table->table)
		return STRING_HASH_POINT_ERROR;

	for (size_t i = 0; i < table_size; i++)
		list_init(&string_hash_table->table[i]);

	string_hash_table->table_size = table_size;
	return STRING_HASH_SUCCESS;
}

string_hash_error_t string_hash_insert(struct string_hash_table *string_hash_table, const char *key, void *private_data)
{
	if (!string_hash_table || !key)
		return STRING_HASH_POINT_ERROR;

	uint32_t index = string_hash(key, string_hash_table->table_size);

	// 遍历链表检查是否已存在
	list_item *pos, *tmp;
	list_for_each_safe(pos, tmp, &string_hash_table->table[index])
	{
		struct string_hash_node *node = container_of(pos, struct string_hash_node, list);
		if (strcmp(node->key, key) == 0) {
			node->private_data = private_data;
			return STRING_HASH_SUCCESS;
		}
	}

	// 新建节点
	struct string_hash_node *new_node = (struct string_hash_node *)malloc(sizeof(struct string_hash_node));
	if (!new_node)
		return STRING_HASH_POINT_ERROR;

	new_node->key = strdup(key);
	if (!new_node->key) {
		free(new_node);
		return STRING_HASH_POINT_ERROR;
	}

	new_node->private_data = private_data;
	list_add_tail(&string_hash_table->table[index], &new_node->list);
	return STRING_HASH_SUCCESS;
}

void *string_hash_find(struct string_hash_table *string_hash_table, const char *key, string_hash_error_t *error)
{
	if (!string_hash_table || !key) {
		if (error)
			*error = STRING_HASH_POINT_ERROR;
		return NULL;
	}

	uint32_t index = string_hash(key, string_hash_table->table_size);

	list_item *pos, *tmp;
	list_for_each_safe(pos, tmp, &string_hash_table->table[index])
	{
		struct string_hash_node *node = container_of(pos, struct string_hash_node, list);
		if (strcmp(node->key, key) == 0) {
			if (error)
				*error = STRING_HASH_SUCCESS;
			return node->private_data;
		}
	}

	if (error)
		*error = STRING_HASH_KEY_NOT_FOUND;
	return NULL;
}

string_hash_error_t string_hash_delete(struct string_hash_table *string_hash_table, const char *key)
{
	if (!string_hash_table || !key)
		return STRING_HASH_POINT_ERROR;

	uint32_t index = string_hash(key, string_hash_table->table_size);

	list_item *pos, *tmp;
	list_for_each_safe(pos, tmp, &string_hash_table->table[index])
	{
		struct string_hash_node *node = container_of(pos, struct string_hash_node, list);
		if (strcmp(node->key, key) == 0) {
			list_delete_item(pos);
			free(node->key);
			free(node);
			return STRING_HASH_SUCCESS;
		}
	}

	return STRING_HASH_KEY_NOT_FOUND;
}

string_hash_error_t string_hash_get_all_keys(struct string_hash_table *string_hash_table, char ***keys, size_t *num_keys)
{
	if (!string_hash_table || !keys || !num_keys)
		return STRING_HASH_POINT_ERROR;

	size_t total_keys = 0;
	for (size_t i = 0; i < string_hash_table->table_size; ++i) {
		list_item *pos, *n;
		list_for_each_safe(pos, n, &string_hash_table->table[i]) total_keys++;
	}

	if (total_keys == 0) {
		*keys = NULL;
		*num_keys = 0;
		return STRING_HASH_SUCCESS;
	}

	char **key_array = (char **)malloc(total_keys * sizeof(char *));
	if (!key_array)
		return STRING_HASH_POINT_ERROR;

	size_t index = 0;
	for (size_t i = 0; i < string_hash_table->table_size; ++i) {
		list_item *pos, *n;
		list_for_each_safe(pos, n, &string_hash_table->table[i])
		{
			struct string_hash_node *node = container_of(pos, struct string_hash_node, list);
			key_array[index] = strdup(node->key);
			if (!key_array[index]) {
				for (size_t j = 0; j < index; ++j)
					free(key_array[j]);
				free(key_array);
				return STRING_HASH_POINT_ERROR;
			}
			index++;
		}
	}

	*keys = key_array;
	*num_keys = total_keys;
	return STRING_HASH_SUCCESS;
}

void destroy_string_hash_table(struct string_hash_table *string_hash_table)
{
	if (!string_hash_table)
		return;

	for (size_t i = 0; i < string_hash_table->table_size; ++i) {
		list_item *pos, *tmp;
		list_for_each_safe(pos, tmp, &string_hash_table->table[i])
		{
			struct string_hash_node *node = container_of(pos, struct string_hash_node, list);
			list_delete_item(pos);
			free(node->key);
			free(node);
		}
	}

	free(string_hash_table->table);
}
