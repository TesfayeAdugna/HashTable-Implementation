/*
 * here are all of the functions and interface declarations
 */
struct Binding;
typedef struct Binding Binding;
struct HashTable;
typedef struct HashTable HashTable;
struct HashTable *create();
unsigned int hash(const char *key);
struct Binding *key_value_pair(const char *key, int value);
bool add(struct HashTable *table, const char *key, int value);
struct Binding *find(struct HashTable *table, const char *key);
bool remove(struct HashTable *table, const char *key);
void delete_table(struct HashTable *table);