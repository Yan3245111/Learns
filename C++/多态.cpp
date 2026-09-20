#include <iostream>
#include <vector>
using namespace std;


class Base {
public:
    // 必须是虚函数 才能实现多态
    virtual void speak() {
        cout << "animals speak" << endl;
    }
};


class Dog: public Base {
public:
    void speak() {
        cout << "dog speak" << endl;
    }
};


class Cat: public Base {
public:
    void speak() {
        cout << "cat speak" << endl;
    }
};


int main() {
    Dog dog;
    dog.speak();  //  直接调用子类的方法

    Cat cat;
    cat.speak();

    // 多态 输出子类的方法
    Base *base = &dog;
    base->speak();

    // 实际使用 获取各自在做的事情
    vector<Base*> anmimals = {&dog, &cat};
    for (Base* animal: anmimals) {
        animal->speak();
    }
    delete base;
}