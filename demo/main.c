#include <stdio.h>
#include <time.h>
#include <string.h>
#include "../include/klang.h"

void
itoa(int num) {
    int digits = 0;
    int x = num;
    while(x) {
        x /= 10;
        digits++;
    }

    char string[digits+1];
    string[digits] = '\0';
    while(num) {
        string[--digits] = (num%10)+'0';
        num /= 10;
    }
    printf("ITOA: %s\n", string);
}

int
main(int argc, char *argv[]) {
    k_array_t *array = array_create();
    char *s = "Hello, world!";
    k_object_t *string = object_create(s, strlen(s), K_STRING);
    k_hashtable_t *ht = hashtable_create();

    char buffer[1024];

    srand(time(NULL));
    itoa(12345);
    while(1) {
        printf("> ");
        scanf("%s", buffer);
        if(buffer[0] == 'q') {
            break;
        }
        if(buffer[0] == 'c') {
            int num = rand() % 1024;
            k_object_t *number = object_create(&num, sizeof(int), K_INTEGER);
            array_append(array, number);
        }
        if(buffer[0] == 'p') {
            printf("Max length: %d\n", array->base.length);
            int i;
            for(i = 0; i < array->base.length; i++) {
                k_object_t *object = array_get(array, i);
                printf("%d ", *(int *)object->data);
            }
            printf("\n");
        }
        if(buffer[0] == 'r') {
            array_remove(array, array->base.length-1);
        }
        if(buffer[0] == 'e') {
            printf("%s\n", string->data);
        }
        if(buffer[0] == 'h') {
            int num = rand() % 1024;
            k_object_t *base = object_create(&num, sizeof(int), K_INTEGER);
            k_object_t *key = object_clone(base);
            k_object_t *value = object_clone(base);
            
            hashtable_insert(ht, key, value);
            printf("Hashtable M: %d\n", ht->max_length);
            printf("Hashtable N: %d\n", ht->base.length);
            object_destroy(base);
        }
        if(buffer[0] == 'j') {
            k_array_t *val = (k_array_t *)hashtable_get(ht, string);
            printf("Key: %s\n", string->data);
            printf("Value: ");
            int i;
            for(i = 0; i < array->base.length; i++) {
                k_object_t *object = array_get(array, i);
                printf("%d ", *(int *)object->data);
            }
            printf("\n");
        }
        if(buffer[0] == 'k') {
            k_object_t *object = (k_object_t *)ht;
            k_hashcell_t *cells = (k_hashcell_t *)object->data;
            
            int i;
            for(i = 0; i < ht->max_length; i++) {
                if(cells[i].status & STATUS_FILLED) {
                    printf(
                        "Key: %d | Value: %d\n", 
                        *(int *)cells[i].key->data, 
                        *(int *)cells[i].value->data
                    );
                }
            }
        }
    }
    printf("Quitting klang interpreter...\n");
    array_destroy(array);
    object_destroy(string);
    hashtable_destroy(ht);
}