#include "hashmap.h"

void freeData(void* data) {
    free(data);
}

HashMap* createHashMap(int capacity) {
    HashMap* map = (HashMap*)malloc(sizeof(HashMap));
    map->capacity = capacity;
    map->data = (LinkedList**)malloc(sizeof(LinkedList*) * map->capacity);
    map->size = 0;

    for (int i = 0; i < map->capacity; i++) {
        map->data[i] = createList(freeData);
    }

    return map;
}

unsigned long hash(HashMap* map, char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash % map->capacity;
}

void push_hash(HashMap* map, char* key, void* data) {
    if (map->size >= map->capacity / 2) {
        printf("Rehashing\n");
        LinkedList** oldData = map->data;
        map->data = (LinkedList**)malloc(sizeof(LinkedList*) * map->capacity * 2);
        map->capacity *= 2;

        for (int i = 0; i < map->capacity; i++) {
            map->data[i] = createList(freeData);
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

    int index = hash(map, key);
    OuterNode* outerNode = (OuterNode*)malloc(sizeof(OuterNode));
    strcpy(outerNode->key, key);
    outerNode->data = data;
    push(map->data[index], outerNode);

    map->size++;
}

void* get(HashMap* map, char* key) {
    void* current = getValue(map->data[hash(map, key)], 0);
    int i = 0;
    while (current != NULL && strcmp(((OuterNode*)current)->key, key) != 0)
    {
        i++;
        current = getValue(map->data[hash(map, key)], i); 
    }

    return ((OuterNode*)current)->data;
}

void freeHashMap(HashMap* map) {
    for (int i = 0; i < map->capacity; i++) {
        freeList(map->data[i]);
    }

    free(map->data);
    free(map);
}