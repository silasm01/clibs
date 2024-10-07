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
  Node* current;

  if (list->cachedNode != NULL && list->cachedIndex != -1) {
    int distCached = abs(list->cachedIndex - index);
    int distHead = abs(0 - index);
    int distTail = abs(list->size - 1 - index);

    if (distCached < distHead && distCached < distTail) {
      current = list->cachedNode;
      i = list->cachedIndex;
    }
  } else if (index < list->size / 2) {
    current = list->head;
  } else {
    current = list->tail;
    i = list->size - 1;
  }

  while (current != NULL && i != index) {
    if (i < index) {
      current = current->next;
      i++;
    } else {
      current = current->prev;
      i--;
    }
  }

  if (current == NULL) {
    return NULL;
  }

  if (i != 0 && i != list->size - 1) {
    list->cachedNode = current;
    list->cachedIndex = i;
  }

  return current;
}

void validateCache(LinkedList* list, int index, Node* current) {
  if (list->cachedNode == current || list->cachedIndex == index) {
    list->cachedNode = NULL;
    list->cachedIndex = -1;
  }
}

LinkedList* createList(void (*freeData)(void*)) {
  LinkedList* list = malloc(sizeof(LinkedList));
  list->head = NULL;
  list->tail = NULL;
  list->size = 0;
  list->freeData = freeData;

  list->cachedNode = NULL;
  list->cachedIndex = -1;

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

int insert(LinkedList* list, void* data, int index) {
  if (index == list->size+1) {
    push(list, data);
    return 0;
  }
  Node* current = getNode(list, index);

  if (current == NULL) {
    return 1;
  }

  Node* node = createNode(data, current->prev, current);

  if (current == list->head) {
    list->head = node;
  }

  list->size++;

  return 0;
}

void* getValue(LinkedList* list, int index) {
  Node* current = getNode(list, index);

  if (current == NULL) {
    return NULL;
  }

  return current->data;
}

int freeList(LinkedList* list) {
  if (list == NULL) {
    return 1;
  }

  Node* current = list->head;
  int i = 0;
  while (current != NULL && i < list->size) {
    Node* next = current->next;
    if (list->freeData != NULL) list->freeData(current->data);
    else return 1;
    free(current);
    i++;
    current = next;
  }

  free(list);

  return 0;
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

int removeNode(LinkedList* list, int index) {
  Node* current = getNode(list, index);

  if (current == NULL) {
    return 1;
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

  validateCache(list, index, current);

  if (list->freeData != NULL) list->freeData(current->data);
  else free(current->data);

  free(current);
  list->size--;

  return 0;
}