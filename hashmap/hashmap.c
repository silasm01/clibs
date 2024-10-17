#include "hashmap.h"

unsigned long hash(HashMap* map, char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash % map->capacity;
}

HashMap* createHashMap(int capacity, void (*freeData)(void*)) {
    HashMap* map = (HashMap*)malloc(sizeof(HashMap));
    map->data = (LinkedList**)malloc(sizeof(LinkedList*) * capacity);
    map->size = 0;
    map->capacity = capacity;

    for (int i = 0; i < capacity; i++) {
        map->data[i] = createList(freeData);
    }

    return map;
}

void resize(HashMap* map) {
    LinkedList** oldData = map->data;
    map->data = (LinkedList**)malloc(sizeof(LinkedList*) * map->capacity * 2);
    map->capacity *= 2;

    for (int i = 0; i < map->capacity; i++) {
        map->data[i] = createList(oldData[0]->freeData);
    }

    for (int i = 0; i < map->capacity / 2; i++) {
        Node* current = oldData[i]->head;
        int j = 0;
        while (current != NULL && j < oldData[i]->size) {
            OuterNode* outerNode = (OuterNode*)current->data;
            push(map->data[hash(map, outerNode->key)], outerNode);
            current = current->next;
            j++;
        }
    }

    return;
}

void push_hash(HashMap* map, char* key, void* data) {
    if (map->size * 2 >= map->capacity) {
        resize(map);
    }

    int index = hash(map, key);
    
    OuterNode* outerNode = (OuterNode*)malloc(sizeof(OuterNode));
    strcpy(outerNode->key, key);
    outerNode->data = data;

    push(map->data[index], outerNode);
    map->size++;
}

void* get(HashMap* map, char* key) {
    int index = hash(map, key);
    Node* current = map->data[index]->head;
    
    for (int i = 0; i < map->data[index]->size; i++) {
        if (current == NULL) {
            return NULL;
        }

        OuterNode* outerNode = (OuterNode*)current->data;
        if (strcmp(outerNode->key, key) == 0) {
            return outerNode->data;
        }

        current = current->next;
    }

    return NULL;
}

void freeHashMap(HashMap* map) {
    for (int i = 0; i < map->capacity; i++) {
        freeList(map->data[i]);
    }

    free(map->data);
    free(map);
}

void remove_hash(HashMap* map, char* key) {
    int index = hash(map, key);

    Node* current = map->data[index]->head;

    for (int i = 0; i < map->data[index]->size; i++) {
        if (current == NULL) {
            return;
        }

        OuterNode* outerNode = (OuterNode*)current->data;
        if (strcmp(outerNode->key, key) == 0) {
            removeNode(map->data[index], i);
            map->size--;
            return;
        }

        current = current->next;
    }
    
    return;
}

void printHashMap(HashMap* map, char* (*printData)(void*)) {
    char* str = (char*)malloc(sizeof(char) * 100);
    strcpy(str, "{");
    int stringSize = 1;

    for (int i = 0; i < map->capacity; i++) {
        Node* current = map->data[i]->head;
        for (int j = 0; j < map->data[i]->size; j++) {
            OuterNode* outerNode = (OuterNode*)current->data;
            if (stringSize + strlen(outerNode->key) + strlen(printData(outerNode->data)) + 10 >= 100) {
                str = (char*)realloc(str, sizeof(char) * (stringSize + 100));
            }
            stringSize += sprintf(str + stringSize, "\"%s\": %s, ", outerNode->key, printData(outerNode->data));
            current = current->next;
        }
    }

    str[stringSize - 2] = '}';

    printf("%s\n", str);

    free(str);

    return;
}

void setCustomHashFree(HashMap* map, char* key, void (*freeData)(void*)) {
    int index = hash(map, key);

    Node* current = map->data[index]->head;

    for (int i = 0; i < map->data[index]->size; i++) {
        if (current == NULL) {
            return;
        }

        OuterNode* outerNode = (OuterNode*)current->data;
        if (strcmp(outerNode->key, key) == 0) {
            map->data[index]->freeData = freeData;
            return;
        }

        current = current->next;
    }

    return;
}