#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <memory.h>
typedef struct Item {
    char *info;
    int reltype;
    int key1;
    char *key2;
    int ind2;
    struct Item *next;
} Item;

typedef struct Node2 {
    int release;
    Item *info;
    struct Node2 *next;
} Node2;

typedef struct KeySpace1 {
    int key1;
    int release;
    Item *info;
} KeySpace1;

typedef struct KeySpace2 {
    char *key2;
    Node2 *node;
    struct KeySpace2 *next;
} KeySpace2;

typedef struct Pointers {
    KeySpace2 *next;
} Pointers;

typedef struct Table {
    KeySpace1 *ks1;
    Pointers *ks2;
    int msize1;
    int msize2;
    Item *first;   //связь с элементом таблицы
    int ind;
} Table;

const char *msgs[] = {"0. Quit", "1. Add", "2. Find", "3. Delete", "4. Find_Key_KS1", "5. Find_Key_KS2", "6. Show",
                      "7. Refresh1", "8. Refresh2", "9. DeleteKey1", "10. DeleteKey2"};
const int MSGS_SIZE = sizeof(msgs) / sizeof(msgs[0]);
int getInt(int *a);
char *get_str();
int dialog(const char *msgs[], int n);

int CreateTable(Table *Table);
int Add(Table *Table);



int main() {
    int(*fptr[])(Table *) = {NULL, Add, Find, Delete, Find_Key_KS1, Find_Key_KS2, Show, Refresh1, Refresh2, Delete_Key1,
                             Delete_Key2};
    int c;
    Table Table = {NULL, NULL, 0, 0, NULL, 0};
    CreateTable(&Table);
    while ((c = dialog(msgs, MSGS_SIZE)) != 0) {
        if (fptr[c](&Table)) {
            break;
        }
    }
    ClearTable(&Table);
    return 0;
}


/*--------------get functinos--------------------------*/
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
/*-----------------------------------------------------*/

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

/*----------------main functions------------------------*/
int Add(Table *Table) {
    if (Table->ind == Table->msize1) {
        printf("You cannot add element, because Table1 is full");
        return 0;
    }
    char *info;
    char *key2;
    int key1;
    printf("Insert key1:");
    getInt(&key1);
    printf("Insert key2:");
    key2 = get_str();
    printf("Insert info:");
    info = get_str();
    Item *head = Table->first;//инициализируем указатель под существующий элемент таблицы и сверяем
    for (;;){
        if (head != NULL){
            int key1;
            int release = 0;
            char *key2;
            char *info;
            if (key1 == head->key1 && strcmp(info, head->info) == 0 && (strcmp(key2, head->key2)) == 0){ //совпадение по 2 ключу,  по первому ключу и по информации
              free(key2);
              free(info);
              printf("Same information and same keys, error\n");
              key2 = NULL;
              info = NULL;
            }
            if(key1 == head->key1 && strcmp(key2, head->key2) == 0){
              release = release + 1;
            }
            head = head->next;
            } else if (head = NULL) {
     //     while (getchar() != '\n');
            break;
            }
        }
    //Добавление элемента
    Item *newelement = (Item *) malloc(sizeof(Item));
    if (Table->first == NULL) {
        Table->first = newelement;   //добавляем если не занят (инициализирован нулем)
        new->next = NULL;
    } else {
        newelement->next = Table->first;   // добавляем новый элемент в таблицу
        Table->first = newelement;
    }

}