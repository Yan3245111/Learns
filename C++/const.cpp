#include <iostream>
using namespace std;

// 修饰常量，不可更改
const int a = 10;
// a = 20; // 错误，常量不可更改

// 修饰指针，在 * 前面，指向的值不可更改，在*后面，指向的值可以更改
int b = 10;
const int *p = &b;
// *p = &c; // 错误，指针指向的值不可更改

int* const c = &b;
// a = &c; // 错误，指针不可更改

// 修饰函数，不可更改函数的参数和返回值
const int add(const int a, const int b) {
    return a + b;
}

// 修饰成员函数, 创建const对象只能调用const函数，不可调用非const函数
class MyClass {
    private:
        string name;
        int age;
    public:
        MyClass(string name, int age) : name(name), age(age) {}
        // name是const成员，不可更改
        string getName() const { 
            return name; 
        }
        void setName(const string& newName) {
            name = newName;
        }

        // 非const函数
        int getAge() {
            return age;
        }

        void setAge(int newAge) {
            age = newAge;
        }
};


int main() {
    // const 对象，只能调用const函数
    const MyClass my_class = MyClass("张三", 18);
    cout << "name=" << my_class.getName() << endl;
    const string new_name = "李四";
    // cout << "age=" << my_class.getAge() << endl;  // 会报错
}