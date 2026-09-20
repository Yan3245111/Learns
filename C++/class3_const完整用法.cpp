/*
函数参数传递
小对象 int，double，指针：使用值传递T，拷贝成本忽略，不改变实参的值
大对象 string/vector/自定义类只读：使用引用，const T&，不改变实参的值
大对象需要修改：T& 引用，零拷贝+可改

默认用const T&, 可改采用T&, 小类型采用值传递
*/
#include <iostream>
using namespace std;


void testCode() {
    int a = 10;

    const int b = 10;
    // b = 20;  // error：a不可更改

    const int* a1 = &a;
    // *a1 = 20;  // error: *a1不可变 a1地址可以 

    int* const a2 = &a;
    *a2 = 20;
    // a2 = &a;  // error: a2地址不可变，*a2值可以 

    const int* const a3 = &a;  // 地址和值都不可变

    const int& r = a;
    // 引用别名，但是加了const，所以r不可变
}


// 常成员函数
class Person {
    string name;

public:
    Person(const string& newName) : name(newName) {}
    const string& getName() const {
        return name;
    }

    void setName(const string& newName) {
        name = newName;
    }
};

// thinking code 写一个Person类，有name和age两个成员，提供const版本的getter和非const的setter，在main里创建cosnt Person对象，测试操作合法
class Person1 {
private:
    string name;
    int age;
public:
    Person1(const string& newName, int newAge) : name(newName), age(newAge) {}
    string getName() const {
        return name;
    }
    int getAge() const {
        return age;
    }

    void setName(const string& newName) {
        name = newName;
    }

    void setAge(int newAge) {
        age = newAge;
    }
};


/*
面试题：const 和 #define 定义常量的区别？

参考：

类型安全：const 有类型，编译器做类型检查；#define 是预处理文本替换，无类型。

作用域：const 遵循作用域规则；#define 从定义处到文件结束（除非 #undef）。

调试：const 变量在调试器里可见；#define 被替换后看不到。

内存：const 变量有地址（可取 &）；#define 没有。

现代 C++ 推荐用 const / constexpr 替代 #define 定义常量。

*/


int main() {
    const Person1 p11("张三", 18);
    cout << p11.getName() << endl;
    cout << p11.getAge() << endl;
    // p11.setName("李四");  // error: const对象不能调用可改成员函数 
    // p11.setAge(20);  // error: const对象不能调用可改成员函数 


    const Person p1("李四");
    string name = p1.getName();
    cout << name << endl;
    // p1.setName("张三");  // error: const对象不能调用可改成员函数 

    // 非const对象可以调用所有成员函数
    Person p2("李四");
    p2.setName("张三");
    cout << p2.getName() << endl;
    return 0;
}