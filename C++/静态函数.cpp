#include <iostream>
using namespace std;


// 静态成员变量属于类，不属于某个对象，所有对象共享一份，定义必须在类外
class Person {
public:
    static int count;  // 所有对象共享一份
    string name;
    Person(string n): name(n) {
        count++;
        cout << "创建" << name  << ", 成员个数：" << count << endl;
    }
    ~Person() {
        // 每次销毁一个对象，成员-1
        count--;
        cout << "销毁" << name  << ", 成员个数：" << count << endl;
    }
    // 静态函数，只能访问静态成员变量
    static int getCount() {
        return count;
    }
};

int Person::count = 0;


int main() {
    Person P1("张三");
    Person P2("李四");
    {
        Person p3("王五");
        cout << "作用域内人数: " << Person::count << endl;
    } // 在作用域内，运行完先销毁王五
    cout << "作用域外人数: " << Person::count << endl;
    // 获取静态成员， 推荐这么写，使用p1.getCount()也可以，但是不推荐
    cout << "当前人数: " << Person::getCount() << endl;
    return 0;
}