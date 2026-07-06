#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

// exit使用：系统级别调用
void exit_usage() {
    // 退出状态码：0表示正常退出，非0表示异常退出
    exit(0); // 正常退出
    exit(1); // 异常退出
}

// char / unsigned char 区别：主要是用char表示bytes的时候
// 表示bytes的时候 char会认为最高位是符号位，会帮忙扩展，下面举例说明
void diffrent_char_and_unchar() {
    // 16进制即bytes的时候，无符号会帮你进行扩展
    char buf[10];
    unsigned char ubuf[10];
    buf[0] = 0xe7;
    ubuf[0] = 0xe7;
    printf("buf[0] = %x, ubuf[0] = %x\n", buf[0], ubuf[0]);   // ffffffe7, e7
}


// 向上取整数
void ceil_usage() {
    double a = 0.1;
    int64_t b = ceil(a);   // 1
}

void compare_zhizhen() {
    // 错误的做法
    // int *p1 = 1;  // 错误1：将整数赋值给指针，访问未授权的内存区域，段错误
    // int *p;       // 错误2：未初始化指针，指向随机地址，野指针
    // *p = *p1;     // 错误3：非法地址读取，想随机地址写入

    // 正确的做法
    int a = 1;
    int b = 2;
    int *p2 = &a; // 正确：将变量a的地址赋值给指针p2
    int *p3 = &b; // 正确：将变量b的地址赋值给指针p3
    printf("*p2 = %d, *p3 = %d\n", *p2, *p3); // 输出指针指向的值
    *p3 = *p2; // 将p2指向的值赋给p3指向的变量b
    printf("After assignment, *p3 = %d\n", *p3); //
}

void float_compare() {
    // float 精度不准 设法转换未>= or <=
    float a = 0.1;
    if (a >= 0) {
        printf("a >= 0 \n");
    } else {
        printf("a < 0 \n");
    }
    // bool一般用if (!b)
    bool b = false;
    if (!b) {
        printf("b is false \n");
    } else {
        printf("b is true \n");
    }
    // 指针一般用 == NULL判断是否为空，不可建立野指针
    int *p = NULL;
    if (p == NULL) {
        printf("p is NULL \n");
    } else {
        printf("p is not NULL \n");
    }
}

void sizeof_test(char *a) {
    printf("111 sizeof(*a) = %zu\n", sizeof(*a));
}

int main() {
    diffrent_char_and_unchar();
    compare_zhizhen();
    float_compare();
    char a[100];
    printf("222 sizeof(a) = %zu\n", sizeof(a)); // 输出数组a的大小
    sizeof_test(a);
    strcpy(a, "hello"); // 正确：使用strcpy函数将字符串复制到数组中
    printf("a = %s\n", a);
    return 0;
}