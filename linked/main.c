#include "linked.h"

typedef struct Person {
    char* name;
    int age;
} Person;

void freePerson(Person* data) {
    free(data->name);
    free(data);
}

void printPerson(Person* data) {
    printf("Name: %s, Age: %d\n", data->name, data->age);
}

int main() {
    LinkedList* list = createList((void (*)(void*))freePerson);

    Person* p1 = malloc(sizeof(Person));
    p1->name = malloc(50);
    strcpy(p1->name, "John");
    p1->age = 30;

    Person* p2 = malloc(sizeof(Person));
    p2->name = malloc(50);
    strcpy(p2->name, "Jane");
    p2->age = 25;

    push(list, p1);
    push(list, p2);

    printList(list, (void (*)(void*))printPerson);
    printList(list, NULL);

    freeList(list);
    return 0;
}