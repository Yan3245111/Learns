#include <iostream>
using namespace std;


// 函数重载，在同一个作用域内，可以有多个同名函数，但是参数列表不同, 返回值类型可以不同，参数列表必须不同

int add(int a, int b) {
    return a + b;
}

int add(int a, int b, int c) {
    return a + b + c;
}

int add (double a, double b) {
    return a + b;
}

int add (int& a) {
    a++;
    return a;
}

int add (const int& a) {
    return a;
}

int main() {
    cout << add(1, 2) << endl;
    cout << add(1, 2, 3) << endl;
    cout << add(1.0, 2.0) << endl;
    int a = 10;
    const int b = 20;
    cout << add(a) << endl;
    cout << add(b) << endl;
}