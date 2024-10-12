#ifndef CIRCULARBUF_H
#define CIRCULARBUF_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct CircularBuffer {
    void** buffer;
    int head;
    int tail;
    int capacity;
    int size;
    void (*freeData)(void*);
} CircularBuffer;

CircularBuffer* createCircularBuf(int capacity);

void push(CircularBuffer* circularBuf, void* data);

void printCircularBuf(CircularBuffer* circularBuf, char* (*printData)(void*));

void freeCircularBuf(CircularBuffer* circularBuf);

void clearBuffer(CircularBuffer* circularBuf);

void removeData(CircularBuffer* circularBuf);

void* peek(CircularBuffer* circularBuf);

int isEmpty(CircularBuffer* circularBuf);

int isFull(CircularBuffer* circularBuf);

void resize(CircularBuffer* circularBuf, int newCapacity);

#endif // CIRCULARBUF_H