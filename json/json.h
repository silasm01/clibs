#ifndef JSON_H
#define JSON_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include <hashmap.h>
#include <linked.h>

void freeChar(void* data);

char* printChar(void* data);

typedef struct jsonObject {
    void* value;
    int nested;
} jsonObject;

typedef struct NestedNode {
    char* data;
    int index;
} NestedNode;

HashMap* parseJson(char* json, int* nested_done);

char* toJSON(HashMap* hashMap);

#endif // JSON_H