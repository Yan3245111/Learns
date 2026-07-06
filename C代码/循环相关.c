#include <stdint.h>
#include <stdio.h>


void test_for() {
    int i = 0;
    int j = 0;
    for (i = 0; i < 5; i++) {
        printf("i = %d\n", i);
    }
    for (j = 0; j < 5; ++j) {
        printf("j = %d\n", j);
    }
    printf("i = %d, j = %d\n", i, j);  // i = 5, j = 5 因为循环结束会再加一次
    printf("i++ = %d, ++j = %d\n", i++, ++j);  // i++ 先使用 i 的值再自增，所以输出 i = 5，之后 i 变为 6；++j 先自增 j 的值再使用，所以 j 变为 6，然后输出 j = 6
    printf("i = %d, j = %d\n", i, j);  // i = 6, j = 6
}


int main() {
    test_for();
    return 0;
}