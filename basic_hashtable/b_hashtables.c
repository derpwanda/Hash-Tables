#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/****
  Basic hash table key/value pair
 ****/
typedef struct Pair
{
    char *key;
    char *value;
} Pair;

/****
  Basic hash table
 ****/
typedef struct BasicHashTable
{
    int capacity;
    Pair **storage;
} BasicHashTable;

/****
  Create a key/value pair to be stored in the hash table.
 ****/
Pair *create_pair(char *key, char *value)
{
    Pair *pair = malloc(sizeof(Pair));
    pair->key = strdup(key);
    pair->value = strdup(value);

    return pair;
}

/****
  Use this function to safely destroy a hashtable pair.
 ****/
void destroy_pair(Pair *pair)
{
    if (pair != NULL)
    {
        free(pair->key);
        free(pair->value);
        free(pair);
    }
}

/****
  djb2 hash function

  Do not modify this!
 ****/
unsigned int hash(char *str, int max)
{
    unsigned long hash = 5381;
    int c;
    unsigned char *u_str = (unsigned char *)str;

    while ((c = *u_str++))
    {
        hash = ((hash << 5) + hash) + c;
    }

    return hash % max;
}

/****
  Fill this in.

  All values in storage should be initialized to NULL
  (hint: look up `calloc`)
 ****/
BasicHashTable *create_hash_table(int capacity)
{
    BasicHashTable *ht = malloc(sizeof(BasicHashTable));
    ht->capacity = capacity;
    ht->storage = calloc(capacity, sizeof(Pair *));
    //we add the star after pair to NOT make room for the Pair struct

    return ht;
}

/****
  Fill this in.

  If you are overwriting a value with a different key, print a warning.

  Don't forget to free any malloc'ed memory!
 ****/
void hash_table_insert(BasicHashTable *ht, char *key, char *value)
{
    Pair *new_pair = create_pair(key, value);
    //added unsigned
    unsigned int hash_key = hash(key, ht->capacity);

    Pair *stored_pair = ht->storage[hash_key];

    if (stored_pair == NULL)
    {
        ht->storage[hash_key] = new_pair;
    }
    else
    {
        printf("Warning: destroying this pair!\n");
        // destroy_pair(ht->storage[hash_key]);
        destroy_pair(stored_pair);

        ht->storage[hash_key] = new_pair;
    }
}

//   if (stored_pair != NULL)
//   {
//     if(strcmp(key, stored_pair->key) != 0)
//     {
//     printf("Warning: destroying this pair!'%s'/'%s' with '%s'/'%s'\n",
//     stored_pair->key, stored_pair->value, pair->key, pair->value;
//     }
//     destroy_pair(stored_pair);
//   }
//   ht->storage[hash_key] = pair;
// }

/****
  Fill this in.

  Don't forget to free any malloc'ed memory!
 ****/
void hash_table_remove(BasicHashTable *ht, char *key)
{
    //added unsigned
    unsigned int hash_key = hash(key, ht->capacity);
    Pair *stored_pair = ht->storage[hash_key];

    if (stored_pair != NULL)
    {
        destroy_pair(stored_pair);
        ht->storage[hash_key] = NULL;
    }
}

// if (ht->storage[hash_key] == NULL || strcmp(ht-storage[hash_key], ??) )
// {
//   fprintf(stderr, "Unable to remove '%s'", key)
// }else{
//   destroy_pair(ht->storage[hash_key])
//   ht->storage[hash_key] == NULL;
// }

/****
  Fill this in.

  Should return NULL if the key is not found.
 ****/
char *hash_table_retrieve(BasicHashTable *ht, char *key)
{
    unsigned int hash_key = hash(key, ht->capacity);

    if (ht->storage[hash_key] != NULL)
    {
        return ht->storage[hash_key]->value;
    }
    return NULL; //if NULL, return NULL
}

/****
  Fill this in.

  Don't forget to free any malloc'ed memory!
 ****/
void destroy_hash_table(BasicHashTable *ht)
{
    for (int i = 0; i < ht->capacity; i++)
    {
        destroy_pair(ht->storage[i]);
    }
    free(ht->storage);
    free(ht);
}

#ifndef TESTING
int main(void)
{
    struct BasicHashTable *ht = create_hash_table(16);

    hash_table_insert(ht, "line", "Here today...\n");

    printf("%s", hash_table_retrieve(ht, "line"));

    hash_table_remove(ht, "line");

    if (hash_table_retrieve(ht, "line") == NULL)
    {
        printf("...gone tomorrow. (success)\n");
    }
    else
    {
        fprintf(stderr, "ERROR: STILL HERE\n");
    }

    destroy_hash_table(ht);

    return 0;
}
#endif
