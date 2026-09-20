#include <iostream>
using namespace std;

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void print() {
    int a = 10;
    int &b = a;
    b = 20;
    cout << "a=" << a << " b=" << b << endl;
}


// 类似于c的指针，但是不能解引用, 引用必须初始化, 不可以重复绑定
int main() {

    int a = 1, b = 2;
    swap(a, b);
    cout << "a=" << a << " b=" << b << endl;
    print();
    return 0;
}
