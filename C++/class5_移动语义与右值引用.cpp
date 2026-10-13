// 移动语义，vector在函数内部生成，返回的时候，会做内部指针转移，而不是拷贝
#include <vector>
#include <cstring>
#include <iostream>
using namespace std;

/*
左值：有名字，有地址，能取&，活得比较久
右值：没名字的临时值，表达结束就消失，无法取地址
&：取地址运算符，返回左值的地址
&&：右值引用，返回右值的引用
int a = 10;
int *b = &a;  a是左值

int c = a + 5;  // a + 5是右值，不能取地址
*/

// 返回的是右值引用，会做移动语义，而不是拷贝，转移内部指针
vector<int> createVector() {
    vector<int> v(10000);
    return v;
}


class MyString {
    char* data;
    size_t len;
public:
    // 构造函数
    MyString(const char* s) {
        len = strlen(s);
        data = new char[len + 1];
        strcpy(data, s);
    }
    // 拷贝函数
    MyString(const MyString& other) {
        len = other.len;
        data = new char[len + 1];
        strcpy(data, other.data);
    }
    // 赋值运算符
    MyString operator=(const MyString& other) {
        if (this == &other) {
            return *this;
        }
        delete[] data;
        len = other.len;
        data = new char[len + 1];
        strcpy(data, other.data);
        return *this;
    }
    // 移动构造函数
    MyString(MyString&& other) noexcept : data(other.data), len(other.len) {
        len = other.len;
        data = other.data;
        other.len = 0;
        other.data = nullptr;
        cout << "移动构造函数" << data << endl;
    }
    // 移动赋值函数
    MyString& operator=(MyString&& other) noexcept {
        if (this == &other) return *this;
        delete[] data;
        data = other.data;
        len = other.len;
        other.data = nullptr;
        other.len = 0;
        cout << "移动赋值函数" << data << endl;
        return *this;
    }
    // 析构函数
    ~MyString() {
        delete[] data;
    }

};

/*
面试题：什么时候会调用拷贝构造，什么时候会调用移动构造？

参考：

拷贝构造：用左值初始化/赋值时。因为左值后面可能还会用，不能偷它的资源。

移动构造：用右值（临时对象、std::move 转换的结果）初始化/赋值时。右值马上要销毁，偷资源安全。

典型场景：函数返回局部对象、std::move 显式转换、传入临时对象。

优先级：如果有移动构造，编译器对右值优先选移动；没有移动构造就退化为拷贝。
*/


int main() {
    vector<int> v = createVector();
    cout << v.size() << endl;

    MyString s1("hello");
    MyString s2 = s1;
    MyString c = std::move(s1);  // s1被换位右值, c偷走了s1的内存, s1的内存被置为nullptr
    MyString d("world");
    d = std::move(c);  // d被换位右值, d偷走了c的内存, c的内存被置为nullptr
    return 0;
}