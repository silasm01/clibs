#ifndef HASHMAP_H
#define HASHMAP_H

#include <linked.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct OuterNode {
    char key[50];
    void* data;
} OuterNode;

void freeData(void* data);

typedef struct HashMap {
    LinkedList** data;
    int size;
    int capacity;
    void (*freeData)(void*);
} HashMap;

HashMap* createHashMap(int capacity);

unsigned long hash(HashMap* map, char *str);

void push_hash(HashMap* map, char* key, void* data);

void* get(HashMap* map, char* key);

void freeHashMap(HashMap* map);

#endif