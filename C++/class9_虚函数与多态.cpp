// 多态
#include <iostream>
using namespace std;

/*
多态的三个必要条件
1.通过基类指针或引用调用
2.调用的是虚函数
3.子类重写了该虚函数
*/

// 不用虚函数版本
class Animal {
public:
    virtual void speak() {
        cout << "I am an animal" << endl;
    }
};


class Dog : public Animal {
public:
    void speak() override {
        cout << "I am a dog" << endl;
    }
};

/*
面试追问：虚函数是怎么实现的
参考：编译器为每个有虚函数的类生成一张虚函数表，里面存折该类所有虚函数的地址，每个对象内部有一个隐藏指针，指向自己的类
因为每个类都有自己的虚函数表，所有是有开销的
*/

// 规则
/*
规则1：析构函数必须是虚函数，否则在delete的时候，派生类的析构不会被调用，只调用基类的析构函数
规则2：构造函数不能是虚的
规则3：不要再析构函数/构造函数里调用虚函数
规则4：基类override关键字，检查基类是否真的重写了虚函数
规则5：纯虚函数与抽象类，只有纯虚函数的类是抽象类，不能实例化，只能作为基类使用
*/

// 多态的应用  同一套接口，不同实现
// 只有虚函数，抽象类
class Shape {
public:
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual ~Shape() {}
};


class Circle : public Shape {
    double radius;
public:
    Circle(double radius) : radius(radius) {}
    double area() const override {
        return 3.1415926 * radius * radius;
    }
    double perimeter() const override {
        return 2 * 3.1415926 * radius;
    }
};


class Rectangle : public Shape {
    double width, height;
public:
    Rectangle(double w, double h) : width(w), height(h) {}
    double area() const override {
        return width * height;
    }
    double perimeter() const override {
        return 2 * (width + height);
    }
};


// 打印
void printArea(const Shape& shape) {
    cout << "Area: " << shape.area() << endl;
}


int main() {
    // Dog dog;
    // dog.speak();
    // Animal * animal = &dog;  // 不用虚函数，即使指针p指向了dog，也会调用Animal的speak方法，使用虚函数可以实现多态效果
    // animal->speak();
    // 多态
    Circle circle(5);
    Rectangle rectangle(3, 5);
    printArea(circle);
    printArea(rectangle);
    cout << "Perimeter: " << circle.perimeter() << endl;
    cout << "Perimeter: " << rectangle.perimeter() << endl;
}
