#include <iostream>
using namespace std;

class Person {
    private:
        string name;
        int age;
    public:
        void setName(string name) {
            this->name = name;
        }

        void setAge(int age) {
            this->age = age;  
        }

        string getName() {
            return name;
        }

        int getAge() {
            return age;
        }
};


// 构造函数
class Person1 {
    int age;
    public:
        // age是成员变量，a是参数 等同于this->age = a
        Person1(int a): age(a) {};

};

int main() {
    // 栈对象
    Person person;
    person.setName("张三");
    person.setAge(18);
    cout << person.getName() << endl;
    cout << person.getAge() << endl;
    // 堆对象 需要手动释放
    Person *p = new Person();
    delete p;
}