#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define INIT_SIZE 7      // 初始桶大小（质数）
#define LOAD_FACTOR 0.75 // 负载因子阈值

// 三个状态：空、已占用、已删除（删除时用）
typedef enum { EMPTY, OCCUPIED, DELETED } Status;

// 键值对
typedef struct {
    int key;
    int value;
    Status status;
} Entry;

// 哈希表
typedef struct {
    Entry* entries;   // 动态数组
    int size;         // 当前桶数量
    int count;        // 实际存储的键值对数量
} HashTable;

void resize(HashTable* table);

// 哈希函数
int hashFunc(int key, int size) {
    return key % size;
}

// 创建哈希表
HashTable* createTable(int size) {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    if (!table) return NULL;
    table->size = size;
    table->count = 0;
    table->entries = (Entry*)calloc(size, sizeof(Entry));
    if (!table->entries) {
        free(table);
        return NULL;
    }
    // 初始化所有状态为 EMPTY
    for (int i = 0; i < size; i++) {
        table->entries[i].status = EMPTY;
    }
    return table;
}

// 插入（线性探测）
void insert(HashTable* table, int key, int value) {
    // 如果负载因子超标，扩容
    if ((float)table->count / table->size >= LOAD_FACTOR) {
        // 扩容逻辑见下方
        resize(table);
    }

    int index = hashFunc(key, table->size);
    int start = index;
    int i = 0;

    // 线性探测：找到空位或已删除位
    while (table->entries[index].status == OCCUPIED) {
        if (table->entries[index].key == key) {
            // 键已存在，更新值
            table->entries[index].value = value;
            return;
        }
        i++;
        index = (start + i) % table->size;
        // 防止死循环（理论上不会，因为负载因子 < 1）
        if (i == table->size) {
            printf("哈希表已满，插入失败\n");
            return;
        }
    }

    // 插入新节点
    table->entries[index].key = key;
    table->entries[index].value = value;
    table->entries[index].status = OCCUPIED;
    table->count++;
}

// 查找
int search(HashTable* table, int key) {
    int index = hashFunc(key, table->size);
    int start = index;
    int i = 0;

    while (table->entries[index].status != EMPTY) {
        if (table->entries[index].status == OCCUPIED && 
            table->entries[index].key == key) {
            return table->entries[index].value;
        }
        i++;
        index = (start + i) % table->size;
        if (i == table->size) break;
    }
    return -1; // 未找到
}

// 删除（标记为 DELETED，不能直接置 EMPTY，否则查找链会断）
void deleteKey(HashTable* table, int key) {
    int index = hashFunc(key, table->size);
    int start = index;
    int i = 0;

    while (table->entries[index].status != EMPTY) {
        if (table->entries[index].status == OCCUPIED && 
            table->entries[index].key == key) {
            table->entries[index].status = DELETED;
            table->count--;
            printf("删除键 %d 成功\n", key);
            return;
        }
        i++;
        index = (start + i) % table->size;
        if (i == table->size) break;
    }
    printf("键 %d 不存在\n", key);
}

// 扩容（重新哈希）
void resize(HashTable* table) {
    int oldSize = table->size;
    Entry* oldEntries = table->entries;

    // 新表大小：找下一个质数（这里简单取 2 倍 + 1）
    int newSize = oldSize * 2 + 1;

    // 分配新表
    Entry* newEntries = (Entry*)calloc(newSize, sizeof(Entry));
    if (!newEntries) {
        printf("扩容失败\n");
        return;
    }
    for (int i = 0; i < newSize; i++) {
        newEntries[i].status = EMPTY;
    }

    // 重新插入所有旧数据
    table->entries = newEntries;
    table->size = newSize;
    table->count = 0;

    for (int i = 0; i < oldSize; i++) {
        if (oldEntries[i].status == OCCUPIED) {
            insert(table, oldEntries[i].key, oldEntries[i].value);
        }
    }

    free(oldEntries);
    printf("扩容完成：%d -> %d\n", oldSize, newSize);
}

// 打印哈希表状态（调试用）
void printTable(HashTable* table) {
    printf("\n=== 哈希表状态 ===\n");
    printf("容量: %d, 元素数: %d, 负载因子: %.2f\n", 
           table->size, table->count, (float)table->count / table->size);
    for (int i = 0; i < table->size; i++) {
        char statusChar;
        switch (table->entries[i].status) {
            case EMPTY: statusChar = 'E'; break;      // Empty
            case OCCUPIED: statusChar = 'O'; break;   // Occupied
            case DELETED: statusChar = 'D'; break;    // Deleted
        }
        if (table->entries[i].status == OCCUPIED) {
            printf("[%d] %c -> key=%d, value=%d\n", 
                   i, statusChar, table->entries[i].key, table->entries[i].value);
        } else {
            printf("[%d] %c\n", i, statusChar);
        }
    }
    printf("==================\n\n");
}

// 销毁哈希表
void destroyTable(HashTable* table) {
    free(table->entries);
    free(table);
}

int main(void) {
    HashTable* table = createTable(INIT_SIZE);
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
    deleteKey(table, 2);
    printf("删除2后查找2: %d\n", search(table, 2));
    destroyTable(table);
    return 0;   
}