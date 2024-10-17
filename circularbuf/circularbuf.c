#include "circularbuf.h"

CircularBuffer* createCircularBuf(int capacity, void (*freeData)(void*)) {
    CircularBuffer* circularBuffer = (CircularBuffer*)malloc(sizeof(CircularBuffer));
    circularBuffer->buffer = (void**)malloc(sizeof(void*) * capacity);
    circularBuffer->head = 0;
    circularBuffer->tail = 0;
    circularBuffer->capacity = capacity;
    circularBuffer->size = 0;
    printf("freeData: %p\n", freeData);
    circularBuffer->freeData = freeData;

    return circularBuffer;
}

void push(CircularBuffer* circularBuf, void* data) {
    circularBuf->buffer[circularBuf->head] = data;

    circularBuf->head = (circularBuf->head + 1) % circularBuf->capacity;

    if (circularBuf->size == circularBuf->capacity) {
        circularBuf->tail = (circularBuf->tail + 1) % circularBuf->capacity;
    }

    if (circularBuf->size < circularBuf->capacity) {
        circularBuf->size++;
    }
}

void printCircularBuf(CircularBuffer* circularBuf, char* (*printData)(void*)) {
    int i = circularBuf->tail;

    char* str = malloc(sizeof(char) * 10);
    strcpy(str, "[");
    
    for (int j = 0; j < circularBuf->size; j++) {
        char* dataStr = printData(circularBuf->buffer[i]);

        str = realloc(str, sizeof(char) * (strlen(str) + strlen(dataStr) + 3));

        strcat(str, dataStr);
        strcat(str, ", ");
        i = (i + 1) % circularBuf->capacity;
    }

    str[strlen(str) - 2] = '\0';
    strcat(str, "]");

    printf("%s\n", str);
}

void freeCircularBuf(CircularBuffer* circularBuf) {
    free(circularBuf->buffer);
    free(circularBuf);
}

void clearBuffer(CircularBuffer* circularBuf) {
    for (int i = 0; i < circularBuf->size; i++) {
        circularBuf->freeData(circularBuf->buffer[i]);
    }

    circularBuf->head = 0;
    circularBuf->tail = 0;
    circularBuf->size = 0;
}

void removeData(CircularBuffer* circularBuf) {
    if (circularBuf->size == 0) {
        return;
    }

    if (circularBuf->size == 1) {
        circularBuf->freeData(circularBuf->buffer[circularBuf->tail]);
        circularBuf->tail = 0;
        circularBuf->head = 0;
        circularBuf->size = 0;
        return;
    }

    free(circularBuf->buffer[circularBuf->tail]);
    circularBuf->tail = (circularBuf->tail + 1) % circularBuf->capacity;
    circularBuf->size--;
}

void* peek(CircularBuffer* circularBuf) {
    if (circularBuf->size == 0) {
        return NULL;
    }

    return circularBuf->buffer[circularBuf->tail];
}

int isFull(CircularBuffer* circularBuf) {
    return circularBuf->size == circularBuf->capacity;
}

int isEmpty(CircularBuffer* circularBuf) {
    return circularBuf->size == 0;
}

void resize(CircularBuffer* circularbuf, int capacity) {
    void** newBuffer = (void**)malloc(sizeof(void*) * capacity);

    int i = circularbuf->tail;
    for (int j = 0; j < circularbuf->size; j++) {
        newBuffer[j % capacity] = circularbuf->buffer[i];
        i = (i + 1) % circularbuf->capacity;
    }

    free(circularbuf->buffer);

    circularbuf->buffer = newBuffer;
    circularbuf->size = circularbuf->size > capacity ? capacity : circularbuf->size;
    circularbuf->head = circularbuf->size;
    circularbuf->tail = 0;
    circularbuf->capacity = capacity;

}

// Create a function that returns this type of string: {
//     "kind": {
//         "graph": true
//     },
//     "nodes": [
//         {
//             "id": "1000",
//             "label": "0xa00003190",
//             "color": "lightblue",
//             "shape": "box"
//         },
//         {
//             "id": "__0x766972646779632f@1__",
//             "label": "0x766972646779632f",
//             "shape": "box"
//         }
//     ],
//     "edges": [
//         {
//             "from": "1000",
//             "to": "__0x766972646779632f@1__",
//             "label": "*circularBuf->buffer"
//         }
//     ]
// }
// The function should take a CircularBuffer* as an argument and return the string. Here it should be noted that each node should be each element in the circularbuffer connected with an arrow specified in edges:
char* graph(CircularBuffer* circularBuf, char* (*printPerson)(void*)) {
    char* str = malloc(sizeof(char) * 1000);
    strcpy(str, "{\n    \"kind\": {\n        \"graph\": true\n    },\n    \"nodes\": [\n");

    for (int i = 0; i < circularBuf->size; i++) {
        char* dataStr = printPerson(circularBuf->buffer[i]);

        str = realloc(str, sizeof(char) * (strlen(str) + strlen(dataStr) + 100));

        char* id = malloc(sizeof(char) * 100);
        sprintf(id, "\"%d\"", i);

        strcat(str, "        {\n");
        strcat(str, "            \"id\": ");
        strcat(str, id);
        strcat(str, ",\n");
        strcat(str, "            \"label\": ");
        strcat(str, dataStr);
        strcat(str, ",\n");
        strcat(str, "            \"color\": \"lightblue\",\n");
        strcat(str, "            \"shape\": \"box\"\n");
        strcat(str, "        },\n");

        free(dataStr);
        free(id);
    }

    str[strlen(str) - 2] = '\0';
    strcat(str, "\n    ],\n    \"edges\": [\n");

    for (int i = 0; i < circularBuf->size; i++) {
        char* from = malloc(sizeof(char) * 100);
        sprintf(from, "\"%d\"", i);

        char* to = malloc(sizeof(char) * 100);
        sprintf(to, "\"%d\"", (i + 1) % circularBuf->size);

        strcat(str, "        {\n");
        strcat(str, "            \"from\": ");
        strcat(str, from);
        strcat(str, ",\n");
        strcat(str, "            \"to\": ");
        strcat(str, to);
        strcat(str, ",\n");
        strcat(str, "            \"label\": \"*circularBuf->buffer\"\n");
        strcat(str, "        },\n");

        free(from);
        free(to);
    }

    str[strlen(str) - 2] = '\0';

    strcat(str, "\n    ]\n}");

    return str;
}