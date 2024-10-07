#include "linked.h"

void printInt(void* data) {
  printf("%d\n", *(int*)data);
}

int main() {
    LinkedList* list = createList(free);

    for (int i = 0; i < 10; i++) {
        int* data = malloc(sizeof(int));
        *data = i;
        push(list, data);
    }

}