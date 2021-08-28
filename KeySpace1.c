#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Table.h"

int Find_Key_KS1(Table *Table) {
    if (Table->ks1 == NULL || Table->ind == 0) {
        printf("Maybe you add elements in KeySpace1? Or you just want to search a monkey flip?\nOk, get it->\nMONKEY FLIP!\n");
        return 0;
    }
    int key1, i, j = 0;
    ///Ввод
    printf("What you want to search?\n1. Find All elements with this key\n2. Find specific element\n");
    getInt(&i);
    if (i == 1) {
        printf("Insert key1:");
        getInt(&key1);
        KeySpace1 *space = NULL;
        for (i = 0; i < Table->ind; i++) {
            if (key1 == Table->ks1[i].key1) {
                j += 1;
                space = realloc(space, sizeof(KeySpace1) * j);
                space[--j].release = Table->ks1[i].release;
                space[j].key1 = Table->ks1[i].key1;
                space[j].info = Table->ks1[i].info;
                j += 1;
            }
        }
        if (space == NULL) {
            printf("Keys1 weren't found!\n");
            return 0;
        } else {
            for (i = 0; i < j; i++) {
                printf("%d %d %s\n", space[i].release, space[i].key1, space[i].info->info);
            }
            free(space);
            return 0;
        }
    } else if (i == 2) {
        int release;
        printf("Insert key1:");
        getInt(&key1);
        printf("Insert release of key1:");
        getInt(&release);
        printf("\n");
        KeySpace1 *space = NULL;
        for (i = 0; i < Table->ind; i++) {
            if (key1 == Table->ks1[i].key1 && release == Table->ks1[i].release) {
                space = malloc(sizeof(KeySpace1));
                space->key1 = Table->ks1[i].key1;
                space->release = Table->ks1[i].release;
                space->info = Table->ks1[i].info;
                printf("%d %d %s\n", space->release, space->key1, space->info->info);
                free(space);
                break;
            }
        }
        if (space == NULL) {
            printf("Keys1 weren't found!\n");
            return 0;
        }
    } else {
        printf("Insert 1 or 2. Not a string, not a 0, not a number > 2. Just 1 or 2! ONE OR TWO!");
    }
    ///
    return 0;
}

int Refresh1(Table *Table) {
    if (Table->ks1 == NULL) {
        printf("You dont even have KeySpace1!");
        return 0;
    }
    int key1, j = 0;
    if (Table->ind == 0) {
        printf("You have no elements in KeySpace!");
        return 0;
    }
    printf("Insert key you want refresh to:");
    getInt(&key1);
    for (int i = Table->ind - 1; i >= 0; i--) {
        if (key1 == Table->ks1[i].key1) {
            ++j;
            if (j > 1) {
                Table->ks1[i].key1 = Table->ks1[Table->ind].key1;
                Table->ks1[i].release = Table->ks1[Table->ind].release;
                Table->ks1[i].info = Table->ks1[Table->ind].info;
                Table->ind -= 1;
            }
        }
    }
    if (j == 0) {
        printf("haha there is no key in table1");
    } else if (j == 1) {
        printf("ummm i found key1 but it is alone");
    };
    return 0;
}

int Delete_Key1(Table *Table) {
    if (Table->ks1 == NULL || Table->ind == 0) {
        printf("listen, i know, it is a sad true, but...You dont have items in KeySpace1. Don't worry, it can be solved - just add items in it and chill\n");
        return 0;
    }
    int key1, j = 0;
    printf("Insert key you want to delete:");
    getInt(&key1);
    KeySpace2 *keyspace2 = NULL;
    Item *search = NULL, *item = NULL, *prev = NULL;
    Node2 *node, *node1 = NULL;
    for (int i = Table->ind - 1; i >= 0; i--) {
        if (key1 == Table->ks1[i].key1) {
            item = Table->ks1[i].info;
            Table->ks1[i].key1 = Table->ks1[Table->ind].key1;
            Table->ks1[i].release = Table->ks1[Table->ind].release;
            Table->ks1[i].info = Table->ks1[Table->ind].info;
            Table->ind -= 1 ;
            keyspace2 = Table->ks2[item->ind2].next;
            j = 0;
            while (keyspace2 != NULL) {
                if (strcmp(keyspace2->key2, item->key2) == 0) {         //item - элемент в основной таблице
                    node = keyspace2->node;                      //node - прошлый элемент
                    node1 = keyspace2->node;                     //node1 - следующий элемент
                    while (node1 != NULL) {                             //keyspace2 - ключи из ячейки во 2 пространстве
                        if (node1->info == item) {                      //search - указатель для поиска элемента в таблице
                            if (node == node1) {                        //удаляем элемент из ks2, если он первый
                                keyspace2->node = keyspace2->node->next;
                                free(node);
                                j++;
                                break;
                            } else {
                                node->next = node1->next;               //удаляем элемент из ks2, если он не первый
                                free(node1);
                                j++;
                                break;
                            }
                        }
                        node = node1;
                        node1 = node1->next;
                    }
                }
                if (j >= 0) break;         //если нашли, то танцуем breakданс
                keyspace2 = keyspace2->next;
            }
            search = Table->first;
            prev = search;
            while (search != item) {    //ищем ключ в таблице, чтобы потом его удалить
                prev = search;
                search = search->next;
            }
            if (Table->first == search) {  //удаляем элемент из таблицы, если он первый
                Table->first = search->next;
                free(search->key2);
                free(search->info);
                free(search);
            } else {
                prev->next = search->next;  //удаляем элемент из таблицы, если он второй
                free(search->key2);
                free(search->info);
                free(search);
            }
        }
    }
    return 0;
}