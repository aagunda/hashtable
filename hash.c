/*
 * hash.c
 *
 * Author: aagunda
 * Description: simple hashtable implementation
 */ 


/***************************************************************************/
/* Includes                                                                */
/***************************************************************************/
#include "hash.h"


/***************************************************************************/
/* Function Definitions                                                    */
/***************************************************************************/
hash_table_t* ht_create(size_t table_size, unsigned long (*hash_func)(void*))
{
  hash_table_t* new_table = malloc(sizeof(*new_table));
  new_table->table = calloc(table_size, sizeof(*new_table->table));
  new_table->table_size = table_size;
  new_table->hash_func = hash_func;

  return new_table;
  
}


int ht_add(hash_table_t* hash_table, void* key, size_t key_size, void* val, size_t val_size)
{
  size_t hash_key = hash_table->hash_func(key) % hash_table->table_size;
    
  if(hash_table->table[hash_key])
  {
    htnode_t* curr_node = hash_table->table[hash_key];
    while(curr_node)
    {
      if(!memcmp(curr_node->key, key, key_size))
        return -1;
      else
        curr_node = curr_node->next;
    }
  }
  
  htnode_t* new_node = malloc(sizeof(*new_node));
  
  new_node->next = hash_table->table[hash_key] ? hash_table->table[hash_key] : NULL;
  new_node->key = malloc(key_size);
  new_node->val = malloc(val_size);
  
  memcpy(new_node->key, key, key_size);
  memcpy(new_node->val, val, val_size);
  
  hash_table->table[hash_key] = new_node;
  
  return 0;
  
}


int ht_remove(hash_table_t* hash_table, void* key, size_t key_size)
{
  size_t hash_key = hash_table->hash_func(key) % hash_table->table_size;
  
  if(hash_table->table[hash_key])
  {
    htnode_t* curr_node = hash_table->table[hash_key];
    htnode_t* last_node = NULL;
    while(curr_node)
    {
      if(!memcmp(curr_node->key, key, key_size))
      {
        if(last_node)
          last_node->next = curr_node->next;
        else
          hash_table->table[hash_key] = curr_node->next;
        
        free(curr_node->key);
        free(curr_node->val);
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


void* ht_get(hash_table_t* hash_table, void* key, size_t key_size)
{
  size_t hash_key = hash_table->hash_func(key) % hash_table->table_size;
  
  if(hash_table->table[hash_key])
  {
    htnode_t* curr_node = hash_table->table[hash_key];
    while(curr_node)
    {
      if(!memcmp(curr_node->key, key, key_size))
        return curr_node->val;
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

