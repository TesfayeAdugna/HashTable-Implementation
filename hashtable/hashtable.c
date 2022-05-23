#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "./hashtable.h"
#define BUCKET_COUNT 1024
/*
 * here are the struct implementations for both the binding and the hashtable.
 */
struct Binding{
    char *key;
    int value;
    struct Binding *next;
};
struct HashTable{
    struct Binding* buckets[BUCKET_COUNT];
};
/* 
 * This create function creates and initializes a hashtable and 
 * then returns it.
 */
struct HashTable *create(){
    struct HashTable *hashtable = (struct HashTable*) malloc(sizeof(struct HashTable));
    for (int i = 0; i<BUCKET_COUNT; i++){
        hashtable->buckets[i] = NULL;
    }
    return hashtable;
}
/*
 * This hash function accepts the key and then hashes it by the formula given and returns
 * the hashed value
 */
unsigned int hash(const char *key){
    unsigned int value = 0;
    unsigned int key_len = strlen(key);
    for (int i = 0; i<key_len; i++){
        value = value * 37 + key[i];
    }
    value = value%BUCKET_COUNT;
    return value;
}
/*
 * This function accepts the key and the value, then adds them to the binding node
 * and returns the node.
 */
struct Binding *key_value_pair(const char *key, int value){
    struct Binding *entry = (struct Binding*)malloc(sizeof(struct Binding));
    entry->key = malloc(strlen(key) + 1);
    strcpy(entry->key,key);
    entry->value = value;
    entry->next = NULL;
    return entry;
}
/*
 * This add function accepts the hashtable, key and value.
 * it hashes the key and store it on slot. it returns true if the slot is 
 * empty and could add the key value pair there. but if the key already
 * existed there it updates the value and returns false.
 */
bool add(struct HashTable *table, const char *key, int value){
    unsigned int slot = hash(key);
    struct Binding *entry = (struct Binding*)malloc(sizeof(struct Binding));
    entry = table->buckets[slot];
    if (entry == NULL){
        table->buckets[slot] = key_value_pair(key,value);
        return true;
    }
    struct Binding *prev;
    while (entry != NULL){
        if (strcmp(entry->key,key)==0){
            entry->value = value;
            return false;
        }
        prev = entry;
        entry = prev->next;
    }
    prev->next = key_value_pair(key,value);
    return true;
}
/*
 * This function tries to look for the key in hashtable and returns the 
 * node if it finds. but if the key is not in the table it'll return Null.
 */
struct Binding *find(struct HashTable *table, const char *key){
    unsigned int slot = hash(key);
    struct Binding *entry = table->buckets[slot];
    if (entry == NULL){
        return NULL;
    }
    while (entry != NULL){
        if (strcmp(entry->key,key)==0){
            return entry;
        }
        entry = entry->next;
    }
    return NULL;
}
/*
 * This remove function looks for the key in the table and removes the node
 * and frees the space if it finds the key. this function returns true if it
 * gets and deletes the key, otherwise it returns false.
 */
bool remove(struct HashTable *table, const char *key){
    unsigned int slot = hash(key);
    struct Binding *head = table->buckets[slot];
    struct Binding *node = table->buckets[slot];
    if (head == NULL){
        return false;
    }
    while (head != NULL && strcmp(head->key, key)==0){
        node = head;
        head = head->next;
        free(node->key);
        free(node);
        return true;
    }
    while (head != NULL && head->next != NULL){
        if (strcmp(head->next->key, key)==0){
            node = head->next;
            head->next = head->next->next;
            free(node->key);
            free(node);
            return true;
        }
        else{
            head = head->next;
        }
    }
    return false;
}
/*
 * the delete_table function deletes the whole table.
 */
void delete_table(struct HashTable *table){
    for (int i=0; i< BUCKET_COUNT; i++){
        struct Binding *entry = table->buckets[i];
        struct Binding *temp = table->buckets[i];

        if (entry == NULL){
            continue;
        }
        for (;;){
            temp = entry;
            if (entry->next == NULL){
                free(temp);
                break;
            }
            entry = entry->next;
            free(temp);
        }
        table->buckets[i] = NULL;
    }
}