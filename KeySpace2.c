#include "Table.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int Find_Key_KS2(Table *Table) {
    if (Table->ks2 == NULL) {
        printf("You cant find key WHEN YOU DON'T HAVE KEYSPACE2");
        return 0;
    }
    int i;
    char *key2;
    Pointers *point = NULL;
    printf("What you want to search?\n1. Find All elements with this key\n2. Find specific element\n");
    getInt(&i);
    if (i == 1) {
        printf("Insert key2:");
        key2 = get_str();
        int k = hashfunc(key2, Table->msize2);
        KeySpace2 *head = Table->ks2[k].next;
        KeySpace2 *new = NULL;
        while (head != NULL) {
            if (strcmp(key2, head->key2) == 0) {
                if(head->node == NULL){
                    printf("No elements");
                    free(key2);
                    return 0;
                }
                Node2 *head1 = head->node;                                  //Версии ключа
                point = malloc(sizeof(Pointers) * Table->msize2);           //Новая таблица
                new = malloc(sizeof(KeySpace2));                 //Новый ключ
                point[k].next = new;
                new->node = NULL;
                new->next = NULL;
                new->key2 = head->key2;
                while (head1 != NULL) {                                     //Пихаем версии в новую таблицу
                    Node2 *new1 = malloc(sizeof(Node2));
                    new1->next = new->node;
                    new->node = new1;
                    new1->release = head1->release;
                    new1->info = head1->info;
                    head1 = head1->next;
                }
                break;
            }
            head = head->next;
        }
        Node2 *head1 = point[k].next->node;
        Node2 *head2 = head1;
        while (head1 != NULL) {
            printf("%s %d %s\n", point[k].next->key2, head1->release, head1->info->info);
            head2 = head1;
            head1 = head1->next;
            free(head2);
        }
        free(new);
        free(key2);
        free(point);
    } else if(i == 2){
        printf("Insert key2:");
        key2 = get_str();
        printf("Insert release you want to search:");
        int release;
        getInt(&release);
        int k = hashfunc(key2, Table->msize2);
        KeySpace2 *head = Table->ks2[k].next;
        KeySpace2 *new = NULL;
        while (head != NULL) {
            if (strcmp(key2, head->key2) == 0) {
                if(head->node == NULL){
                    printf("No elements");
                    free(key2);
                    return 0;
                }
                Node2 *node = head->node;
                while(node != NULL && node->release != release){
                    node = node->next;
                }
                if(node == NULL){
                    printf("No elements");
                    free(key2);
                    return 0;
                }
                point = malloc(sizeof(Pointers) * Table->msize2);           //Новая таблица
                new = malloc(sizeof(KeySpace2));                 //Новый ключ
                point[k].next = new;
                new->node = malloc(sizeof(Node2));
                new->node->next = NULL;
                new->node->release = node->release;
                new->node->info = node->info;
                new->next = NULL;
                new->key2 = head->key2;
                printf("%d %s %s", new->node->release, new->key2, new->node->info->info);
                free(new->node);
                break;
            }
            head = head->next;
        }
        free(new);
        free(key2);
        free(point);
    } else{
        printf("Insert 1 or 2. Not a string, not a 0, not a number > 2. Just 1 or 2! ONE OR TWO!");
    }
    return 0;
};

int Refresh2(Table *Table) {
    if (Table->ks2 == NULL) {
        printf("You dont even have KeySpace2!");
        return 0;
    }
    printf("Insert key you want to refresh:");
    char *key2;
    key2 = get_str();
    int k = hashfunc(key2, Table->msize2);
    KeySpace2 *head = Table->ks2[k].next;
    while (head != NULL) {
        if (strcmp(key2, head->key2) == 0) {
            if (head->node == NULL) {
                printf("You dont have elements with this key");
                free(key2);
                return 0;
            }
            Node2 *head1 = head->node->next;
            Node2 *head3 = NULL;
            while (head1 != NULL) {
                head3 = head1;
                head1 = head1->next;
                free(head3);
            }
            free(key2);
            head->node->next = NULL;
            return 0;
        }
        head = head->next;
    }
    if (head == NULL) {
        printf("We didnt find this key in KeySpace2");
        free(key2);
    }
    return 0;
}

int Delete_Key2(Table *Table) {
    if(Table->ks2 == NULL){
        printf("Keyspace2 is empty");
        return 0;
    }
    char *key2, j = 0;
    printf("Insert key you want to delete");
    key2 = get_str();
    int hash = hashfunc(key2, Table->msize2);
    KeySpace2 *keySpace2 = Table->ks2[hash].next;             //для поиска ключа
    while (keySpace2 != NULL) {
        if (strcmp(keySpace2->key2, key2) == 0) {
            Node2 *node1 = NULL;                              //текущий элемент
            while (keySpace2->node != NULL) {
                Item *item = keySpace2->node->info;           //элемент из таблицы
                node1 = keySpace2->node;
                keySpace2->node = node1->next;
                for (int i = Table->ind - 1; i >= 0; i--) {
                    if (item == Table->ks1[i].info) {
                        Table->ks1[i].key1 = Table->ks1[Table->ind].key1;
                        Table->ks1[i].release = Table->ks1[Table->ind].release;
                        Table->ks1[i].info = Table->ks1[Table->ind].info;
                        Table->ind -= 1;
                        break;
                    }
                }
                Item *search = Table->first;
                Item *prev = search;
                while (search != item) {    //ищем ключ в таблице, чтобы потом его удалить
                    prev = search;
                    search = search->next;
                }
                if (Table->first == search) {  //удаляем элемент из таблицы, если он первый
                    Table->first = search->next;
                    free(search);
                } else {
                    prev->next = search->next;  //удаляем элемент из таблицы, если он второй
                    free(search);
                }
                free(node1);
            }
            return 0;
        }
        keySpace2 = keySpace2->next;
    }
    free(key2);
    Show(Table);
    return 0;
}