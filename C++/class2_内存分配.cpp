/*
栈：局部变量，函数参数，自动分配，快但小
堆：new/malloc，手动/智能指针分配，慢但大
全局、静态变量: 全局变量，static变量，程序全程存活
常量区：字符串常亮，const常亮
代码区：编译后的机器指令，只读
*/

#include <iostream>
using namespace std;

int globalVar = 100;  // 全局


void testCode() {
    int stackVar = 1; // 栈
    int *heapVar = new int(2); // 堆
    const char* str = "hello";  // 常量区
    cout << "全局变量地址：" << &globalVar << endl;
    cout << "栈变量地址：" << &stackVar << endl;
    cout << "堆变量地址：" << heapVar << endl;
    cout << "常量区地址：" << (void*)str << endl;
    delete heapVar;  // 如果忘记delete 就会内存泄漏
}


int* thinking(int n) {
    int* a = new int[n];  // 注：不要写成new int(5), 代表分配一个int，初始值为5
    for (int i = 0; i < n; i++) {
        a[i] = i * 100;
    }
    return a;
}

/*
面试题：为什么 delete 之后要把指针置为 nullptr？

参考：delete p 只释放了 p 指向的堆内存，但 p 这个变量本身还存着那个已失效的地址，成了悬空指针。如果之后再 delete p 一次，就是对同一块内存重复释放（double free），是未定义行为，通常导致崩溃。
置 nullptr 后，再 delete p 是安全的——C++ 保证 delete nullptr 什么都不做。所以这是防御性编程的习惯。
*/


int main() {
    // testCode();
    int n = 5;
    int* a = thinking(n);
    for (int i = 0; i < n; i++) {
        cout << a[i] << endl;
    }
    delete[] a;  // 如果忘记delete 就会内存泄漏
    a = nullptr;

    int *b = new int(5);
    cout << *b << endl;
    delete b;  // 如果忘记delete 就会内存泄漏
    b = nullptr;
    return 0;
}