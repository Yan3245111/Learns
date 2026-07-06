#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// 二分法必须是线性表，且必须是有序的
uint8_t binary_search(uint8_t list[], uint8_t left, uint8_t right, uint8_t target) {
    if (left > right) {
        return 0; // Not found
    }
    uint8_t mid = left + (right - left) / 2;
    printf("Searching for %d in [%d, %d], mid: %d\n", target, left, right, mid);
    if (list[mid] == target) {
        return mid;
    } else if (target < list[mid]) {
        return binary_search(list, left, mid - 1, target);
    } else {
        return binary_search(list, mid + 1, right, target); 
    }
}


int main() {
    uint8_t list[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    uint8_t target = 5;
    uint8_t size = sizeof(list) / sizeof(list[0]);
    uint8_t result = binary_search(list, 0, size - 1, target);
    if (result) {
        printf("Element %d found at index %d\n", target, result);
    } else {
        printf("Element %d not found in the list\n", target);
    }
    return 0;
}