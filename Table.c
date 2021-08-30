#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Table.h"


int getInt(int *a)
{
    int result =-2;
    for(;;) {
        printf("\nplease input INT number --> ");
        result = scanf("%d", a);
        if (result == 0 ) {
            result =-2;
            while (getchar() != '\n'); // --> очистить стандартный ввод!
            printf("input ERROR repet please! \n");
            continue;
        }
        if (result == -1){
            printf("THE END OF FILE, exit... \n");
            exit(EOF);
        }
        return result;
    }
}

int CreateTable(Table *Table) {
    for(;;){
      printf("Insert size of KeySpace1:");
      getInt(&(Table->msize1));
      printf("Insert size of KeySpace2:");
      getInt(&(Table->msize2));
      if (Table->msize1 <= 0 || Table->msize2 <= 0) {
         printf("You wrote incorrect sizes of KeySpaces, please rewrite them\n");
         while (getchar() != '\n'); //очищение стандартного потока ввода
         continue;
          }
      return 0;
    }
}

char *get_str() {
    char buf[81] = {0};
    char *res = NULL;
    int len = 0;
    int n;
    do {
        n = scanf("%80[^\n]", buf);
        if (n < 0) {
            if (!res) {
                return NULL;
            }
        } else if (n > 0) {
            int chunk_len = (int) strlen(buf);
            int str_len = len + chunk_len;
            res = realloc(res, str_len + 1);
            memcpy(res + len, buf, chunk_len);
            len = str_len;
        } else {
            scanf("%*c");
        }
    } while (n > 0);
    if (len > 0) {
        res[len] = '\0';
    } else {
        res = calloc(1, sizeof(char));
    }
    return res;
}

int dialog(const char *msgs[], int n) {
    char *error = "";
    int choice;
    do {
        puts(error);
        error = "You're wrong. Try again!";
        for (int i = 0; i < n; ++i) {
            puts(msgs[i]);
        }
        puts("Make your choice: ");
        getInt(&choice);
    } while (choice < 0 || choice >= n);
    printf("\n");
    return choice;
}

int Delete(Table *Table) {
    int key1;
    char *key2;
    int release;
    Item *head = Table->first;
    Item *head3 = Table->first;
    int j = 0, i;
    ///Ввод
    printf("Insert key1:");
    getInt(&key1);
    printf("Insert key2:");
    key2 = get_str();
    printf("Choose version you want to delete:");
    getInt(&release);
    ///
    /// Поиск составного ключа
    while ((head != NULL) && (head->key1 != key1 || strcmp(head->key2, key2) != 0 || head->reltype != release)) {
        head3 = head;
        head = head->next;
    }
    if (head == NULL) {
        printf("Connected Key wasn't found!");
        free(key2);
        return 0;
    }
    ///
    ///Поиск ключа1
    for (i = Table->ind - 1; i >= 0; i--) {
        if (key1 == Table->ks1[i].key1 && Table->ks1[i].info == head) {
            Table->ks1[i].key1 = Table->ks1[--(Table->ind)].key1;
            Table->ks1[i].release = Table->ks1[Table->ind].release;
            Table->ks1[i].info = Table->ks1[Table->ind].info;
        }
    }
    ///
    ///Поиск Ключа2
    ///Поиск элемента во втором пространстве
    int k = head->ind2;
    KeySpace2 *head1 = Table->ks2[k].next;
    while (head1 != NULL) {
        if (strcmp(head1->key2, key2) == 0) {
            Node2 *head4 = head1->node;
            Node2 *head2 = head1->node;
            while (head4 != NULL) {
                if (head4->info == head) {
                    if (head2 == head4) {
                        head1->node = head1->node->next;
                        free(head2);
                        j++;
                        break;
                    } else {
                        head2->next = head4->next;
                        free(head4);
                        j++;
                        break;
                    }
                }
                head2 = head4;
                head4 = head4->next;
            }
        }
        if (j >= 0) break;
        head1 = head1->next;
    }
    if (Table->first == head) {
        Table->first = head->next;
        free(head);
    } else {
        head3->next = head->next;
        free(head);
    }
    free(key2);
    return 0;
}

int Find(Table *Table) {
    if (Table->first == NULL) {
        printf("Dude, You dont even have elements! Add it and then comeback!\n");
        return 0;
    }
    int key1;
    char *key2;
    int release;
    Item *head = Table->first;
    ///Ввод
    printf("Insert key1:");
    getInt(&key1);
    printf("Insert key2:");
    key2 = get_str();
    printf("Choose version of element:");
    getInt(&release);
    ///
    /// Поиск составного ключа
    while ((head != NULL)) {
        if (head->key1 == key1 && strcmp(head->key2, key2) == 0 && release == head->reltype) {
            printf("%d %s %s\n", head->key1, head->key2, head->info);
            free(key2);
            return 0;
        }
        head = head->next;
    }
    if (head == NULL) {
        printf("\nConnected Key wasn't found!\n");
        free(key2);
        return 0;
    }
    return 0;
}


int Add_Key1(int key1, Table *Table) {
    int k = Table->ind;
    int release = 0;
    ///Если Нет элементов, то 1 условие, если есть, то 2
    if (k == 0) {
        Table->ks1->key1 = key1;
        Table->ks1->release = 0;
        Table->ks1->info = Table->first;
        (Table->ind)++;
    } else {
        for (int i = 0; i < k; i++) {
            if (Table->ks1[i].key1 == key1) {
                release = Table->ks1[i].release + 1;
            }
        }
        Table->ks1[k].key1 = key1;
        Table->ks1[k].release = release;
        Table->ks1[k].info = Table->first;
        (Table->ind)++;
    }
    return 0;
}

int hashfunc(char *key2, int a) {
    int k = (int) strlen(key2);
    int hash = 7;
    for (int i = 0; i < k; i++) {
        hash = hash * 37 + (key2[i] - '0');
    }
    k = abs(hash) % a;
    return k;
}

int Add_Key2(char *key2, Table *Table) {
    int hash = hashfunc(key2, Table->msize2);
    KeySpace2 *head = Table->ks2[hash].next;
    Table->first->ind2 = hash;
    ///Проверка на существование ключа
    while (head != NULL) {
        if (strcmp(key2, head->key2) == 0) {
            Node2 *new1 = malloc(sizeof(Node2));
            new1->next = head->node;
            head->node = new1;
            new1->next != NULL ? new1->release = (new1->next->release) + 1 : (new1->release = 0);
            new1->info = Table->first;
            return 0;
        }
        head = head->next;
    }
    ///
    ///Добавление элемента, если ключ не нашли
    KeySpace2 *new = malloc(sizeof(KeySpace2));
    new->next = Table->ks2[hash].next;
    Table->ks2[hash].next = new;
    new->node = malloc(sizeof(Node2));
    new->node->info = Table->first;
    new->node->release = 0;
    new->node->next = NULL;
    new->key2 = malloc(strlen(key2) + 1);
    strcpy(new->key2, key2);
    ///
    return 0;
}

int Add(Table *Table) {
    ///Проверка Первого пространства на полноту
    if (Table->ind == Table->msize1) {
        printf("You cannot add element, because Table1 is full");
        return 0;
    }
    int key1, release = 0, j;
    char *key2;
    char *info;
    ///
    ///Ввод ключей и инфы
    printf("Insert key1:");
    getInt(&key1);
    printf("Insert key2:");
    key2 = get_str();
    printf("Insert info:");
    info = get_str();
    ///
    ///Добавление элемента в Таблицу
    Item *head = Table->first;
    while (head != NULL) {
        if ((j = strcmp(key2, head->key2)) == 0 && key1 == head->key1 && strcmp(info, head->info) == 0) {
            printf("We met the same key! You should insert it with different info!\n");
            free(key2);
            free(info);
            return 0;
        } else if (key1 == head->key1 && j == 0) {
            release += 1;
        }
        head = head->next;
    }
    Item *new = (Item *) malloc(sizeof(Item));
    if (Table->first == NULL) {
        Table->first = new;
        new->next = NULL;
    } else {
        new->next = Table->first;
        Table->first = new;
    }
    new->key1 = key1;
    new->key2 = key2;
    new->info = info;
    new->reltype = release;
    ///
    ///Добавление элементов в Пространства
    if (Table->ks1 == NULL) {
        Table->ks1 = malloc(sizeof(KeySpace1) * (Table->msize1));
        Table->ind = 0;
    };
    Add_Key1(key1, Table);
    if (Table->ks2 == NULL) {
        Table->ks2 = malloc(sizeof(Pointers) * (Table->msize2));
        for (int i = 0; i < Table->msize2; i++) {
            Table->ks2[i].next = NULL;
        }
    };
    Add_Key2(key2, Table);
    ///
    return 0;
}

int Show(Table *Table) {
    Item *head = Table->first;
    printf("Table:\n");
    if (head == NULL) {
        printf("There are no Items in Table\n");
    }
    while (head != NULL) {
        printf("%d %d %s %s\n", head->reltype, head->key1,
               head->key2, head->info);
        head = head->next;
    }
    printf("Table1:\n");
    if (Table->ind == 0 || Table->ks1 == NULL) {
        printf("Empty\n");
    }
    for (int i = Table->ind - 1; i >= 0; i--) {
        printf("%d %d %s\n", Table->ks1[i].release, Table->ks1[i].key1, Table->ks1[i].info->info);
    }
    printf("Table2:\n");
    if (Table->ks2 == NULL) {
        printf("Empty\n");
        return 0;
    }
    KeySpace2 *head2 = NULL;
    Node2 *head3 = NULL;
    int j = 0;
    for (int i = 0; i < Table->msize2; i++) {
        head2 = Table->ks2[i].next;
        while (head2 != NULL) {
            head3 = head2->node;
            while (head3 != NULL) {
                ++j;
                printf("%d %s %s\n", head3->release, head2->key2, head3->info->info);
                head3 = head3->next;
            }
            head2 = head2->next;
        }
    }
    if (j == 0) {
        printf("Empty\n");
    }
    return 0;
}

int ClearTable(Table *Table) {
    free(Table->ks1);
    Item *head = Table->first;
    Item *head1 = NULL;
    KeySpace2 *keySpace2 = NULL;
    KeySpace2 *prev = NULL;
    Node2 *node = NULL;
    for(int i = 0; i < Table->msize2; i++) {
        keySpace2 = Table->ks2[i].next;
        while (keySpace2 != NULL) {
            while (keySpace2->node != NULL) {
                node = keySpace2->node;
                keySpace2->node = node->next;
                free(node);
            }
            prev = keySpace2;
            keySpace2 = keySpace2->next;
            Table->ks2[i].next = keySpace2;
            free(prev->key2);
            free(prev);
        }
    }
    while (head != NULL) {
        head1 = head;
        head = head->next;
        free(head1->key2);
        free(head1->info);
        free(head1);
    }
    free(Table->ks2);
    return 0;
}