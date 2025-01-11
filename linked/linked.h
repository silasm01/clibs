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
  void (*freeData)(void*);
} Node;

Node* createNode(void* data, Node* prev, Node* next, void (*freeData)(void*));

typedef struct LinkedList {
  struct Node* head;
  struct Node* tail;

  struct Node* cachedNode;
  int cachedIndex;

  size_t size;
  void (*freeData)(void*);
} LinkedList;

Node* getNode(LinkedList* list, int index);

LinkedList* createList(void (*freeData)(void*));

void push(LinkedList* list, void* data);

int insert(LinkedList* list, void* data, int index);

void* getValue(LinkedList* list, int index);

int freeList(LinkedList* list);

void printList(LinkedList* list, void (*printData)(void*, int));

int removeNode(LinkedList* list, int index);

void sortLinkedList(LinkedList* list, int (*compare)(void*, void*));

void* pop(LinkedList* list);

#endif