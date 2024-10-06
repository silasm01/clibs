#ifndef LINKED_H
#define LINKED_H

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Node {
  void* data;
  struct Node* next;
  struct Node* prev;
} Node;

Node* createNode(void* data, Node* prev, Node* next);

typedef struct LinkedList {
  struct Node* head;
  struct Node* tail;
  size_t size;
  void (*freeData)(void*);
} LinkedList;

Node* getNode(LinkedList* list, int index);

LinkedList* createList(void (*freeData)(void*));

void push(LinkedList* list, void* data);

void insert(LinkedList* list, void* data, int index);

void* getValue(LinkedList* list, int index);

void freeList(LinkedList* list);

void printList(LinkedList* list, void (*printData)(void*));

void removeNode(LinkedList* list, int index);

#endif