#include <stdio.h>
#include <stdlib.h>


// 指针数组
/*
数组本质：连续存储多个指针变量。
*/
int get_arr_num(void) {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int *p = arr; // 指向数据的第一个地址
    for (int i = 0; i < 10; i++) {
        printf("%d\n", *p);
        p++;  // 指针地址+1，指向下一个值得地址
    }
    return 0;
}


void bubble_sort(int *arr, int len) {
    for (int i = 0; i < len - 1; i++) {
        for (int j = 0; j < len - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}


void test_bubble(void) {
    int arr[10] = {9, 7, 5, 8, 2, 4, 1, 6, 3, 10};
    printf("%d\n", sizeof(arr) / sizeof(arr[0]));
    bubble_sort(arr, 10);
    for (int i = 0; i < 10; i++) {
        printf("%d\n", arr[i]);
    }
}


// 枚举
enum Color {
    RED,
    GREEN,
    BLUE
};
void test_enum(void) {
    enum Color color = RED;
    printf("%d\n", color);
    // 直接比对即可
    if (color == RED) {

    }
}


// 位域 结构体
/*
尽量不用有符号，有正负号，比如int a: 2, 为-1 1，有正负号的坑
typedef 是重命名用的，在实例化的时候就可以不写strcut
*/
struct flags
{
    /* data */
    unsigned int a : 1;
    unsigned int b : 2;
    unsigned int c : 2;
};

struct flags flag1;

typedef struct {
    char name[20];
    int age;
} People;

People peo1;


void test_bit(void) {
    flag1.a = 1; // 2会超限报错
    sprintf(peo1.name, "%s", "xiaoming");  // 一般用格式化拼接
    strcpy(peo1.name, "xiaoming");
}


int main(void) {
    // get_arr_num();
    // change_num();
    test_bubble();
    return 0;
}
