/*
当类里面有指针成员时，要使用深度拷贝构造函数和赋值运算符重载，否在在析构函数退出时会出现两次删除指针，导致程序内存泄漏。

赋值运算四步: 1. 检查是否自赋值 2. 释放旧资源 3. 拷贝新资源 4. 返回this
*/

#include <cstring>
#include <iostream>
using namespace std;


class MyString {
    char * data;
    size_t len;
public:
    MyString(const char * s) {
        len = strlen(s);
        data = new char[len + 1];
        strcpy(data, s);
    }

    // 拷贝构造
    MyString(const MyString& other) {
        len = other.len;
        data = new char[len + 1];
        strcpy(data, other.data);
    }

    // 赋值运算符重载
    MyString& operator=(const MyString& other) {
        if (this == &other) return *this;
        delete[] data;
        len = other.len;
        data = new char[len + 1];
        strcpy(data, other.data);
        return *this;
    }

    // 析构函数
    ~MyString() {
        delete[] data;
    }
    const char* getData() const {
        return data;
    }
};


/*
面试题：什么是"浅拷贝"和"深拷贝"？

参考：

浅拷贝：逐成员复制，指针成员复制的是地址，导致两个对象共享同一份资源。

深拷贝：为指针成员重新分配内存，复制指向的内容，两个对象各自独立。

编译器默认生成的拷贝构造/赋值是浅拷贝。当类持有需要手动管理的资源时，
浅拷贝会导致 double free、悬空指针等问题，所以必须自定义为深拷贝（三法则），或者用 RAII 类型（零法则）从根本上避免。
*/


int main() {
    MyString s1("hello");
    // 拷贝构造
    MyString s2 = s1;
    cout << s2.getData() << endl;
    // 赋值运算符重载
    MyString s3("world");
    s3 = s1;
    cout << s3.getData() << endl;
    return 0;
}