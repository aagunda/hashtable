#include <stdio.h>
#include "hash.h"


int main(void)
{
  hash_table_t* test_table = ht_create(20, hash_string);
  
  ht_add(test_table, "aaa", 4, "111", 4);
  ht_add(test_table, "bbb", 4, "222", 4);
  ht_add(test_table, "ccc", 4, "333", 4);
  ht_add(test_table, "ddd", 4, "444", 4);
  ht_add(test_table, "eee", 4, "555", 4);
  ht_add(test_table, "fff", 4, "666", 4);
  ht_add(test_table, "ggg", 4, "777", 4);
  ht_add(test_table, "ggg", 4, "888", 4);
  
  printf("%s\n", (char*)ht_get(test_table, "aaa", 4));
  printf("%s\n", (char*)ht_get(test_table, "bbb", 4));
  printf("%s\n", (char*)ht_get(test_table, "ccc", 4));
  printf("%s\n", (char*)ht_get(test_table, "ddd", 4));
  printf("%s\n", (char*)ht_get(test_table, "eee", 4));
  printf("%s\n", (char*)ht_get(test_table, "fff", 4));
  printf("%s\n", (char*)ht_get(test_table, "ggg", 4));
  
  ht_remove(test_table, "aaa", 4);
  ht_remove(test_table, "bbb", 4);
  ht_remove(test_table, "ccc", 4);
  ht_remove(test_table, "ddd", 4);
  ht_remove(test_table, "eee", 4);
  ht_remove(test_table, "fff", 4);
  ht_remove(test_table, "ggg", 4);
  
  printf("%s\n", (char*)ht_get(test_table, "aaa", 4));
  printf("%s\n", (char*)ht_get(test_table, "bbb", 4));
  printf("%s\n", (char*)ht_get(test_table, "ccc", 4));
  printf("%s\n", (char*)ht_get(test_table, "ddd", 4));
  printf("%s\n", (char*)ht_get(test_table, "eee", 4));
  printf("%s\n", (char*)ht_get(test_table, "fff", 4));
  printf("%s\n", (char*)ht_get(test_table, "ggg", 4));
  
  return 0;
}

