#include <stdint.h>


struct bit_field {
    uint8_t a : 3;
    uint8_t b : 5;
} bits;


typedef struct {
    uint8_t a;
    uint8_t b;
} test;


// 函数指针使用typedef定义别名

int my_function1(int x) {
    return x * 2;
}

typedef void (*func_ptr)(int);  // 返回void的函数指针类型
func_ptr my_function2 = my_function1;  // 声明一个函数=指针变量，并将其初始化为指向my_function1函数


int main() {
    bits.a = 5; // 3 bits can hold values from 0 to 7
    bits.b = 20; // 5 bits can hold values from 0 to

    struct bit_field bits1;
    bits1.a = 7; // 3 bits can hold values from 0 to 7


    // typedef 用来为已有的类型创建别名的关键字，给现有类型起新名字
    typedef struct bit_field bit_field_t;
    bit_field_t bits2;
    bits2.a = 3; // 3 bits can hold values from 0 to 7
    

    // 有typedef的可不用struct，直接用别名来定义变量
    test Test1;
    
    return 0;
}
