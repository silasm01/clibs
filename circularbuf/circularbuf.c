#include "circularbuf.h"

CircularBuffer* createCircularBuf(int capacity) {
    CircularBuffer* circularBuffer = (CircularBuffer*)malloc(sizeof(CircularBuffer));
    circularBuffer->buffer = (void**)malloc(sizeof(void*) * capacity);
    circularBuffer->head = 0;
    circularBuffer->tail = 0;
    circularBuffer->capacity = capacity;
    circularBuffer->size = 0;

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
    circularbuf->head = circularbuf->size;
    circularbuf->tail = 0;
    circularbuf->capacity = capacity;
    circularbuf->size = circularbuf->size > capacity ? capacity : circularbuf->size;

}