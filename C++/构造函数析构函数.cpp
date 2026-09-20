#include <iostream>
using namespace std;

// 构造函数，对象创建时自动调用，初始化对象，没有返回值
// 析构函数，对象销毁时自动调用，用于清理资源

class Person {
private:
    string name;
    int age;
public:
    // 构造函数 无构造参数
    Person() {
        name = "张三";
        age = 18;
        cout << "构造函数 创建person对象" << endl;
    }
    // 构造函数 有构造参数
    /*
    Person(string name, int age) : name(name), age(age) {
    cout << "构造函数 创建person对象" << endl;
    }
    // 等同于下面这种
    Person(string name, int age) {
        this->name = name;
        this->age = age;
        cout << "构造函数 创建person对象" << endl;
    }
    */
    
    // 析构函数 使用栈创建时，需要手动delete，不然不会调用析构函数
    ~Person() {
        cout << "析构函数 销毁person对象" << endl;
    }
    // 普通成员函数
    void display() {
        cout << "姓名：" << name << endl;
        cout << "年龄：" << age << endl;
    }
};


// 拷贝构造函数
class Animals {
private:
    string name;
    int age;
public:
    Animals(string name, int age) : name(name), age(age) {
        cout << "构造函数 创建animals对象" << endl;
    }
    // 拷贝构造函数
    Animals(const Animals& other) {
        name = other.name;
        age = other.age;
        cout << "拷贝构造函数 创建animals对象" << endl;
    }
};


int main() {
    cout << "start" << endl;
    Person p1;
    p1.display();
    cout << "end" << endl;

    // 拷贝创建对象
    Animals a1("cat", 1);
    Animals a2(a1);
    // 等同于
    // Animals a2 = a1;
    return 0;
}