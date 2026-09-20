#include <iostream>
using namespace std;


/*
引用：必须初始化，不能为空，不能改绑，指针可以
引用不占独立内存，指针式独立变量
引用更安全，指针更灵活

小类型int，double用值传递
大类型，string，vector用const T&引用，避免拷贝
需要修改实参用引用或者指针, 但是const T&引用不能修改值
*/
void testCode1(int a) {
    a = 100;
}


// 引用：传递的是别名，所以会改变原变量的值
void testCode2(int& a) {
    a = 100;
}


// 传递的是指针，所以会改变原变量的值
void testCode3(int* a) {
    *a = 100;
}


void change(int * p) {
    int y = 10;
    p = &y;
}

void minMan(int arr[], int n, int& minVal, int& maxVal) {
    for (int i = 0; i < n; i++) {
        if (arr[i] < minVal) {
            minVal = arr[i];
        }
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
    }
}


// 下面两个题，哪个是对的，为什么
 int * thinking1() {
    int *a = new int[3];
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;
    return a;
}

// 错误：数组是栈内存，不能返回指针，否则会报错，运行到int a[3]就结束了
int * thinking2() {
    int a[3] = {1, 2, 3};
    return a;
}


/*
面试题：const int& r = 10; 这行代码合法吗？为什么？

参考：合法。10 是临时值（右值），普通引用 int& 不能绑定它，但 const 引用可以绑定临时值，编译器会为这个临时值创建一个隐藏的变量，
让 r 引用它，并延长其生命周期到 r 的作用域结束。这是 C++ 的一个重要特性，也是"const 引用能接收字面量"的原因。
*/


int main() {
    // int a = 1, b = 1, c = 1;
    // testCode1(a);
    // testCode2(b);
    // testCode3(&c);
    // cout << a << endl;
    // cout << b << endl;
    // cout << c << endl;  
    // int x = 5;
    // change(&x);
    // cout << x << endl;
    int *a = thinking1();
    cout << a[0] << endl;
    cout << a[1] << endl;
    cout << a[2] << endl;
    delete[] a;  // 如果忘记delete 就会内存泄漏

    // ERROR
    int *b = thinking2();
    cout << b[0] << endl;
    cout << b[1] << endl;
    cout << endl;
}