#include <stdlib.h>
#include "Table.h"
#include "KeySpace1.h"
#include "KeySpace2.h"

const char *msgs[] = {"0. Quit", "1. Add", "2. Find", "3. Delete", "4. Find_Key_KS1", "5. Find_Key_KS2", "6. Show",
                      "7. Refresh1", "8. Refresh2", "9. DeleteKey1", "10. DeleteKey2"};
const int MSGS_SIZE = sizeof(msgs) / sizeof(msgs[0]);

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
