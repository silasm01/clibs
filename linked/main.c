#include "linked.h"

int main() {
    // Create a new linked list with integer data
    LinkedList* list = createList(free);

    // Add some data to the list
    for (int i = 0; i < 10; i++) {
        int* data = malloc(sizeof(int));
        *data = i;
        push(list, data);
    }

    // Print list backwards
    Node* current = list->tail;
    while (current != NULL) {
        int* data = current->data;
        printf("%d\n", *data);
        current = current->prev;
    }

    // forward
    printList(list, NULL);

    // Free the list
    if (freeList(list) == 1) {
        printf("Error freeing list\n");
        return 1;
    }
}