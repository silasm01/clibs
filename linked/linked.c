#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linked.h"

Node* createNode(void* data, Node* prev, Node* next) {
  Node* node = malloc(sizeof(Node));
  node->data = data;

  if (prev != NULL) {
    prev->next = node;
    node->prev = prev;
  } else {
    node->prev = NULL;
  }

  if (next != NULL) {
    next->prev = node;
    node->next = next;
  }

  return node;
}

Node* getNode(LinkedList* list, int index) {
  int i = 0;
  int count = 0;
  Node* current;

  if (index < list->size / 2) {
    current = list->head;
    while (current != NULL && i < index) {
      current = current->next;
      count++;
      i++;
    }
  } else {
    current = list->tail;
    i = list->size - 1;
    while (current != NULL && i > index) {
      current = current->prev;
      count++;
      i--;
    }
  }

  // printf("Count: %d\n", count);

  if (current == NULL) {
    return NULL;
  }

  return current;
}

LinkedList* createList(void (*freeData)(void*)) {
  LinkedList* list = malloc(sizeof(LinkedList));
  list->head = NULL;
  list->tail = NULL;
  list->size = 0;
  list->freeData = freeData;

  return list;
}

void push(LinkedList* list, void* data) {
  Node* node = createNode(data, list->tail, NULL);

  if (list->head == NULL) {
    list->head = node;
    list->tail = node;
  } else {
    list->tail = node;
  }
  list->size++;
}

void insert(LinkedList* list, void* data, int index) {
  Node* current = getNode(list, index);

  if (current == NULL) {
    return;
  }

  Node* node = createNode(data, current->prev, current);

  if (current == list->head) {
    list->head = node;
  }

  list->size++;

  return;
}

void* getValue(LinkedList* list, int index) {
  Node* current = getNode(list, index);

  if (current == NULL) {
    return NULL;
  }

  return current->data;
}

void freeList(LinkedList* list) {
  Node* current = list->head;
  int i = 0;
  while (current != NULL && i < list->size) {
    Node* next = current->next;
    if (list->freeData != NULL) list->freeData(current->data);
    else free(current->data);
    free(current);
    i++;
    current = next;
  }

  free(list);
}

void printList(LinkedList* list, void (*printFunction)(void*)) {
  Node* current = list->head;
  int i = 0;
  while (current != NULL && i < list->size) {
    if (printFunction != NULL) printFunction(current->data);
    else printf("%d\n", *(int*)current->data);
    current = current->next;
    i++;
  }
}

void removeNode(LinkedList* list, int index) {
  Node* current = getNode(list, index);

  if (current == NULL) {
    return;
  }

  if (current == list->head) {
    list->head = current->next;
  }

  if (current == list->tail) {
    list->tail = current->prev;
  }

  if (current->prev != NULL) {
    current->prev->next = current->next;
  }

  if (current->next != NULL) {
    current->next->prev = current->prev;
  }

  if (list->freeData != NULL) list->freeData(current->data);
  else free(current->data);

  free(current);
  list->size--;
}