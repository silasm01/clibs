#ifndef JSON_H
#define JSON_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <hashmap.h>

void freeChar(void* data);

char* printChar(void* data);

typedef struct jsonObject {
    void* value;
    int nested;
} jsonObject;

HashMap* parseJson(char* json);

char* toJSON(HashMap* hashMap);

#endif // JSON_H