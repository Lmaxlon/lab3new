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

typedef struct {
    KeySpace2 *next;
} Pointers;

typedef struct {
    KeySpace1 *ks1;
    Pointers *ks2;
    int msize1;
    int msize2;
    Item *first;
    int ind;
} Table;

int getInt(int *a);

char *get_str();

int dialog(const char *msgs[], int n);

int Add_Key1(int key1, Table *Table);

int hashfunc(char *key2, int a);

int Add_Key2(char *key2, Table *Table);

int Add(Table *Table);

int Find(Table *Table);

int Delete(Table *Table);

int Show(Table *Table);

int CreateTable(Table *Table);

int ClearTable(Table *Table);
