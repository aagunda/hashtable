//hash tables
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




typedef struct ht_node {
	struct ht_node* next;
	void* key;
	void* value;
} htnode_t;


typedef struct hash_table {
	htnode_t** table;
	size_t table_size;
	unsigned long (*hash_func)(void*);
} hash_table_t;


hash_table_t* ht_create(size_t table_size, unsigned long (*hash_func)(void*))
{
	hash_table_t* new_table = malloc(sizeof(*new_table));
	new_table->table = calloc(table_size, sizeof(*new_table->table));
	new_table->table_size = table_size;
	new_table->hash_func = hash_func;

  return new_table;
  
}


void ht_add(hash_table_t* hash_table, void* key, void* value)
{
  size_t hash_key = hash_table->hash_func(key) % hash_table->table_size;
  
  htnode_t* new_node = malloc(sizeof(*new_node));
  
  new_node->next = hash_table->table[hash_key] ? hash_table->table[hash_key] : NULL;
  new_node->key = key;
  new_node->value = value;
  
  hash_table->table[hash_key] = new_node;
  
}


int ht_remove(hash_table_t* hash_table, void* key)
{
  size_t hash_key = hash_table->hash_func(key) % hash_table->table_size;
  
  if(hash_table->table[hash_key])
  {
    htnode_t* curr_node = hash_table->table[hash_key];
    htnode_t* last_node = NULL;
    while(curr_node)
    {
      if(curr_node->key == key)
      {
        if(last_node)
          last_node->next = curr_node->next;
        else
          hash_table->table[hash_key] = curr_node->next;
        
        free(curr_node->key);
        free(curr_node->value);
        free(curr_node);
        
        return 0;
      }
      else
      {
        last_node = curr_node;
        curr_node = curr_node->next; 
      } 
    }
  }
  
  return -1;
  
}


void* ht_get(hash_table_t* hash_table, void* key)
{
  size_t hash_key = hash_table->hash_func(key) % hash_table->table_size;
  
  if(hash_table->table[hash_key])
  {
    htnode_t* curr_node = hash_table->table[hash_key];
    while(curr_node)
    {
      if(curr_node->key == key)
        return curr_node->value;
      else
        curr_node = curr_node->next;
    }
  }
  
  return NULL;

}


unsigned long hash_string(void* string)
{
  unsigned long hash = 0;
  
  char* chstring = (char*)string;
  int cur_char;
  
  while(cur_char = *chstring++)
    hash = cur_char + (hash << 16) + (hash << 6) - hash;
    
  return hash;
}


int main(void)
{
  hash_table_t* test_table = ht_create(20, hash_string);
  char* key1 = malloc(4*sizeof(char));
  char* val1 = malloc(4*sizeof(char));
  char* key2 = malloc(4*sizeof(char));
  char* val2 = malloc(4*sizeof(char));
  char* key3 = malloc(4*sizeof(char));
  char* val3 = malloc(4*sizeof(char));
  
  strcpy(key1, "abc");
  strcpy(val1, "123");
  strcpy(key2, "def");
  strcpy(val2, "456");
  strcpy(key3, "ghi");
  strcpy(val3, "789");
  
  ht_add(test_table, key1, val1);
  ht_add(test_table, key2, val2);
  ht_add(test_table, key3, val3);
  
  printf("%s\n", (char*)ht_get(test_table, key1));
  printf("%s\n", (char*)ht_get(test_table, key2));
  printf("%s\n", (char*)ht_get(test_table, key3));
  
  ht_remove(test_table, key1);
  ht_remove(test_table, key2);
  ht_remove(test_table, key3);
  
  printf("%s\n", (char*)ht_get(test_table, key1));
  printf("%s\n", (char*)ht_get(test_table, key2));
  printf("%s\n", (char*)ht_get(test_table, key3));
  
  return 0;
}
