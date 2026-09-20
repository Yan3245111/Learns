#include <iostream>
using namespace std;


class Singleton {
private:
    static Singleton* instance;
    int value;

    Singleton() : value(0) {}
    ~Singleton() {}

public:
    // 禁止拷贝
    Singleton(const Singleton& other) = delete;
    Singleton& operator=(const Singleton& other) = delete;
    // 静态函数 获取唯一实例
    static Singleton* getInstance() {
        if (instance == nullptr) {
            instance = new Singleton();
        }
        return instance;
    }

    void setValue(int v) {
        value = v;
    }
    int getValue() {
        return value;
    }
    static void destroy() {
        delete instance;
        instance = nullptr;
    }
};

Singleton* Singleton::instance = nullptr;


int main() {
    Singleton* s1 = Singleton::getInstance();
    Singleton* s2 = Singleton::getInstance();
    cout << "s1 == s2: " << (s1 == s2) << endl;
    s1->setValue(100);
    cout << "s1 value: " << s1->getValue() << endl;
    cout << "s2 value: " << s2->getValue() << endl;
    Singleton::destroy();
    return 0;
}