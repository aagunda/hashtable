/*
 * hash.h
 *
 * Author: aagunda
 * Description: simple hashtable implementation
 */ 
 
#ifndef HASH_H
#define HASH_H


/***************************************************************************/
/* Includes                                                                */
/***************************************************************************/
#include <stdlib.h>
#include <string.h>


/***************************************************************************/
/* Typedefs                                                                */
/***************************************************************************/
typedef struct ht_node {
  struct ht_node* next;
  void* key;
  void* val;
} htnode_t;


typedef struct hash_table {
  htnode_t** table;
  size_t table_size;
  unsigned long (*hash_func)(void*);
} hash_table_t;


/***************************************************************************/
/* Function Prototypes                                                     */
/***************************************************************************/
hash_table_t* ht_create(size_t table_size, unsigned long (*hash_func)(void*));
int ht_add(hash_table_t* hash_table, void* key, size_t key_size, void* val, size_t val_size);
int ht_remove(hash_table_t* hash_table, void* key, size_t key_size);
void* ht_get(hash_table_t* hash_table, void* key, size_t key_size);
unsigned long hash_string(void* string);


#endif
