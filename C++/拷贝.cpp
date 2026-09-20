#include <iostream>
#include <cstring>
using namespace std;
// 只要类里面有堆成员，必须用深拷贝

// 浅拷贝:两个对象的指针指向同一个块内存，如果有析构函数，程序退出时相当于调用两次，程序会崩溃
class Person {
private:
    char *name;
    int age;
public:
    Person(const char *n, int a): age(a) {
        name = new char[strlen(n) + 1];
        strcpy(name, n);
    }
    ~Person() {
        delete[] name;
    }
};

// 深拷贝：不仅赋值成员的值，还赋值指针指向的内容，让两个对象各自拥有独立的内存
class Person1 {
private:
    char *name;
    int age;
public:
    Person1(const char* n, int a): age(a) {
        name = new char[strlen(n) + 1];
        strcpy(name, n);
    }
    Person1(const Person1& other): age(other.age) {
        name = new char(strlen(other.name) + 1);
        strcpy(name, other.name);
    }
    ~Person1() {
        delete[] name;
    }
};


int main() {
    Person p1("张三", 18);
    Person p2(p1);
    // p2.name 和p1.name 指向同一块内存，程序退出时会调用两次析构函数，导致内存泄漏，会报错
    return 0;
}