#include <iostream>
#include <cstring>
using namespace std;

// 赋值运算符是在修改已有存在对象的时候使用的
// 有指针成员变量且需要自己管理时，就是new和delete，重载和拷贝函数都需要写，避免内存泄漏
// 没有指针成员，使用浅拷贝即可
class Person {
private:
    char* name;
public:
    Person(const char* n) {
        name = new char[strlen(n) + 1];
        strcpy(name, n);
        cout << "构造函数" << endl;
    }
    // 拷贝构造
    Person(const Person& other) {
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
        cout << "拷贝构造函数" << endl;
    }
    // 赋值运算符
    Person& operator=(const Person& other) {
        if (this != &other) {
            delete[] name;
            name = new char[strlen(other.name) + 1];
            strcpy(name, other.name);
        }
        cout << "赋值运算符" << endl;
        return *this;
    }
    // 析构函数
    ~Person() {
        delete[] name;
        cout << "析构函数" << endl;
    }
};


int main() {
    Person p1("张三");
    // 拷贝构造
    Person p2(p1);
    Person p3 = p1;  // 也是拷贝，不是赋值

    // 赋值，更改已有对象
    Person p4("李四");
    p4 = p1;
    return 0;
}