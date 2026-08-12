#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define HASH_SIZE 31  // 哈希表大小, 建议选择一个质数，必须设置长度，不然无法计算

typedef struct HashNode {
    int key;
    int value;
    struct HashNode *next;
} HashNode;

typedef struct HashTable {
    HashNode* table[HASH_SIZE];
} HashTable;


int hashFunc(int key) {
    return key % HASH_SIZE;
}

// 创建哈希表
HashNode* createNode(int key, int value) {
    HashNode* node = (HashNode*)malloc(sizeof(HashNode));
    if (node == NULL) {
        printf("内存分配失败\n");
        return NULL;
    }
    node->key = key;
    node->value = value;
    node->next = NULL;
    return node;
}

// 插入键值对
void insert(HashTable* table, int key, int value) {
    int index = hashFunc(key);
    HashNode* cur = table->table[index];
    while (cur != NULL) {
        if (cur->key == key) {
            cur->value = value;
            return;
        }
        cur = cur->next;
    }
    HashNode* newNode = createNode(key, value);
    newNode->next = table->table[index];
    table->table[index] = newNode;
}

// 查找键值对
int search(HashTable* table, int key) {
    int index = hashFunc(key);
    HashNode* cur = table->table[index];
    while (cur != NULL) {
        if (cur->key == key) {
            return cur->value;
        }
        cur = cur->next;
    }
    return -1;
}


// 删除键值对
void deleteNode(HashTable* table, int key) {
    int index = hashFunc(key);
    HashNode* cur = table->table[index];
    HashNode* prev = NULL;
    while (cur!= NULL && cur->key != key) {
        prev = cur;
        cur = cur->next;
    }
    if (cur == NULL) { 
        printf("节点不存在\n");
        return;
    }
    if (prev == NULL) {
        table->table[index] = cur->next;
    }
    else {
        prev->next = cur->next;
    }
    free(cur);
}

// 创建哈希表
HashTable* createHashTable() {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    if (!table) {
        return NULL;
    }
    memset(table->table, 0, sizeof(table->table));
    for (int i = 0; i < HASH_SIZE; i++) {
        table->table[i] = NULL;
    }
    return table;
}

// 删除哈希表
void deleteHashTable(HashTable* table) {
    if (table == NULL) {
        return;
    }
    for (int i = 0; i < HASH_SIZE; i++) {
        HashNode* cur = table->table[i];
        while (cur != NULL) {
            HashNode* next = cur->next;
            free(cur);
            cur = next;
        }
    }
    free(table);
}

// 完整测试
int main() {
    HashTable* table = createHashTable();
    if (table == NULL) {
        printf("创建哈希表失败\n");
        return 1;
    }
    insert(table, 1, 100);
    insert(table, 2, 200);
    insert(table, 3, 300);
    printf("查找1: %d\n", search(table, 1));
    printf("查找2: %d\n", search(table, 2));
    printf("查找3: %d\n", search(table, 3));
    printf("查找4: %d\n", search(table, 4));
    deleteNode(table, 2);
    printf("删除2后查找2: %d\n", search(table, 2));
    deleteHashTable(table);
    return 0;
}

