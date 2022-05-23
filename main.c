#include <assert.h>
#include <stdbool.h>
#include "./hashtable/hashtable.c"
#include "./hashtable/hashtable.h"
/*
 * the main function to call all the other functions.
 */
int main(int argc, char **argv){
    struct HashTable *table = create();

    assert(find(table, "Test key") == NULL);
    assert(add(table, "Test key",11)== true);
    assert(add(table, "Test key", 11) == false);
    assert(add(table,"Test keys", 11) == true);

    struct Binding* binding = find(table,"Test key");
    assert(binding != NULL && binding->value == 11);

    delete_table(table);

    return 0;
}