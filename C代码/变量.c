#include <stdio.h>
#include <string.h>

// static 静态函数每次执行的时候还是上一次保留的值
void get_num()
{
    static int num = 0;
    num++;
    printf("%d\n", num);
}

int main(void)
{
    get_num();
}

// * 和 &的区别  *代表的指向地址的内容， &表示的是地址
void compare_zhizhen(void) {
    int a = 1;
    int *b = &a;
    printf("%d %d\n", a, &a);  // a = 1, &a = a的地址
    printf("%d %d\n", *b, b);  // *b =1, b = a 的地址
}
