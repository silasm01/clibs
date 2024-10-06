#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a struct for storing the data (Person)
typedef struct Person {
    char name[50];
    int age;
} Person;

typedef struct HashMap {
  char* key;
  void* value;
} HashMap;