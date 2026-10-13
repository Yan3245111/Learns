#include <iostream>
#include <vector>
using namespace std;


// 多态是用例让调用方不用知道具体类型的
// 还有一个原因，多个类型放进vector列表的时候，没办法写具体的类型，
// 只能写基类的指针或reference_wrapper<Base>包装一下基本，< >没办法写具体的类型

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