#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// 定义链表节点
typedef struct ListNode {
    int val;
    struct ListNode *next;
} ListNode;


// 创建一个新节点
ListNode* createNode(int val) {
    ListNode* node = (struct ListNode*)malloc(sizeof(struct ListNode));
    if (node == NULL) {
        printf("内存分配失败\n");
        return NULL;
    }
    node->val = val;
    node->next = NULL;
    return node;
}


// 插入节点
void insertNode(ListNode** head, int val) {
    ListNode* newNode = createNode(val);
    if (newNode == NULL) {
        return;
    }
    if (*head == NULL) {
        *head = newNode;
    } 
    else {
        newNode->next = *head;
        *head = newNode;
    }
}

// 删除节点
void deleteNode(ListNode** head, int val) {
    ListNode* current = *head;
    ListNode* prev = NULL;
    while (current != NULL && current->val != val) {
        prev = current;
        current = current->next;
    }
    if (current == NULL) {
        printf("节点不存在\n");
        return;
    }
    if (prev == NULL) {
        *head = current->next;
    } else {
        prev->next = current->next;
    }
    free(current);
}

// 遍历链表
void traverseList(ListNode* head) {
    ListNode* current = head;
    while (current != NULL) {
        printf("%d -> ", current->val);
        current = current->next;
    }
    printf("NULL\n");
}

int main(void) {
    ListNode* head = NULL;
    insertNode(&head, 1);
    insertNode(&head, 2);
    insertNode(&head, 3);
    traverseList(head);
    deleteNode(&head, 2);
    traverseList(head);
    return 0;
}
