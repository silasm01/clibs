#include "json.h"

// Create function that parses the json to a hash table
// The function should take a string as an argument and return a hash table

void freeChar(void* data) {
    free(data);
}

char* printChar(void* data) {
    jsonObject* data2 = (jsonObject*)data;
    return data2->value;
}

char* trim(char* str) {
    char* end;

    // Trim leading space
    while (isspace((unsigned char)*str)) {
        str++;
    }

    if (*str == 0) {  // All spaces?
        return str;
    }

    // Trim trailing space
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) {
        end--;
    }

    // Write new null terminator character
    end[1] = '\0';

    return str;
}

HashMap* parseJson(char* json, int* index) {
    HashMap* hashMap = createHashMap(10, freeChar);

    json = trim(json);
    strcpy(json + *index, trim(json + *index));
    (*index)++;

    while (json[*index - 1] != '}')
    {

        char* key = malloc(100);
        int keyIndex = 0;
        strcpy(json + *index, trim(json + *index));
        while (json[*index] != ':') {
            if (json[*index] != '"') {
                key[keyIndex] = json[*index];
                keyIndex++;
            }
            (*index)++;
        }
        key[keyIndex] = '\0';
        key = trim(key);
        (*index)++;
        
        char* value = malloc(100);
        int valueIndex = 0;
        int nested = 0;
        strcpy(json + *index, trim(json + *index));
        while (json[*index] != ',' && json[*index] != '}') {
            if (json[*index] == '{') {
                nested = 1;
                // (*index)++;
                HashMap* nested = parseJson(json, index);
                jsonObject* object = malloc(sizeof(jsonObject));
                object->value = nested;
                object->nested = 1;
                push_hash(hashMap, key, object);
                break;
            }

            if (json[*index] != '"') {
                value[valueIndex] = json[*index];
                valueIndex++;
            }
            (*index)++;
        }
        value[valueIndex] = '\0';
        value = trim(value);
        (*index)++;

        if (nested == 0) {
            jsonObject* object = malloc(sizeof(jsonObject));
            object->value = value;
            object->nested = 0;

            push_hash(hashMap, key, object);
        }
    }
    strcpy(json + *index, trim(json + *index));

    return hashMap;
}

char* toJSON(HashMap* hashMap) {
    char* json = malloc(1000);
    strcpy(json, "{");

    for (int i = 0; i < hashMap->capacity; i++) {
        if (hashMap->data[i] != NULL) {
            Node* current = hashMap->data[i]->head;
            while (current != NULL) {
                OuterNode* outerNode = (OuterNode*)
                current->data;
                jsonObject* object = (jsonObject*)outerNode->data;
                char* key = outerNode->key;

                strcat(json, "\"");
                strcat(json, key);
                strcat(json, "\": ");

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