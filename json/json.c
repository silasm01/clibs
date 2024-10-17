#include "json.h"

// Create function that parses the json to a hash table
// The function should take a string as an argument and return a hash table

void freeChar(void* data) {
    free(data);
}

char* printChar(void* data) {
    return data;
}

HashMap* parseJson(char* json) {
    HashMap* hashMap = createHashMap(10, freeChar);

    char* token = strtok(json, "{}:,\"");

    char* key = NULL;
    char* value = NULL;

    while (token != NULL) {
        if (strcmp(token, " ") == 0) {
                token = strtok(NULL, "}:,\"");
                continue;
        }
        if (token[0] == '\n') {
            token = &token[1];
        }
        while (token[0] == ' ') {
        {
            token = &token[1];
        }
        }

        if (strcmp(token, "") == 0) {
            token = strtok(NULL, "}:,\"");
            continue;
        }

        if (key == NULL) {
            key = strdup(token);  // Save the key
        } else {
          if (strchr(&token[0], '{') != NULL) {
            token = strtok(NULL, "{");
            value = strdup(token);
            // Recursively parse the nested JSON object
            HashMap* nestedHashMap = parseJson(value);
            jsonObject* nestedObject = malloc(sizeof(jsonObject));
            nestedObject->value = nestedHashMap;
            nestedObject->nested = 1;
            push_hash(hashMap, key, nestedObject);

            // setCustomFree(nestedHashMap, key, freeHashMap);
          } else {
            value = strdup(token);
            jsonObject* object = malloc(sizeof(jsonObject));
            // trim space from value
            if (value[strlen(value) - 1] == ' ') {
                value[strlen(value) - 1] = '\0';
            }
            if (value[0] == ' ') {
                value = &value[1];
            }
            object->value = value;
            object->nested = 0;
            push_hash(hashMap, key, object);
          }
            key = NULL;
        }
        token = strtok(NULL, "}:,\"");
    }

    return hashMap;
}

char* toJSON(HashMap* hashMap) {
    char* json = malloc(1000);
    strcpy(json, "{");

    for (int i = 0; i < hashMap->capacity; i++) {
        if (hashMap->data[i] != NULL) {
            printf("i: %d\n", i);
            Node* current = hashMap->data[i]->head;
            while (current != NULL) {
                OuterNode* outerNode = (OuterNode*)
                current->data;
                jsonObject* object = (jsonObject*)outerNode->data;
                char* key = outerNode->key;

                strcat(json, "\"");
                strcat(json, key);
                strcat(json, "\": ");

                printf("key: %s\n", key);

                if (object->nested == 1) {
                    HashMap* value = (HashMap*)object->value;
                    strcat(json, toJSON((HashMap*)value));
                    strcat(json, ", ");
                } else {
                    char* value = (char*)object->value;
                    strcat(json, "\"");
                    strcat(json, value);
                    strcat(json, "\", ");
                }

                current = current->next;
            }
        }
    }

    json[strlen(json) - 2] = '\0';

    strcat(json, "}");

    return json;
}