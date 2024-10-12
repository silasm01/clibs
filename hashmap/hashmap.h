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

typedef struct HashMap {
    LinkedList** data;
    int size;
    int capacity;
} HashMap;

unsigned long hash(HashMap* map, char *str);

HashMap* createHashMap(int capacity, void (*freeData)(void*));

void push_hash(HashMap* map, char* key, void* data);

void* get(HashMap* map, char* key);

void freeHashMap(HashMap* map);

void remove_hash(HashMap* map, char* key);

void resize(HashMap* map);

void printHashMap(HashMap* map, char* (*printData)(void*));

#endif