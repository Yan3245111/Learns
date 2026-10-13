// RALL：智能指针，资源的获取和释放，绑定到对象的构造和析构。
#include <vector>
#include <memory>
#include <iostream>
using namespace std;

void testCode() {
    shared_ptr<int> p = make_shared<int>(10);
    shared_ptr<int> p2 = p;  // 2个智能指针指向同一个内存，在退出时会自动释放内存。维护同一个引用计数，所以不会delete2次
    cout << p.use_count() << endl;
    cout << p2.use_count() << endl;
}

// 三种智能指针
/*
unique_ptr: 唯一指针，只能有一个智能指针指向内存，退出时会自动释放内存, 不能拷贝，只能移动
shared_ptr: 共享指针，多个智能指针可以指向同一个内存，引用计数为0时会自动释放内存
weak_ptr: 弱指针，不能直接访问内存，必须通过lock()转换为shared_ptr才能访问内存，引用计数不增加
*/

void unique_ptrTest() {
    // 一般用唯一指针就够了
    unique_ptr<int> p = make_unique<int>(10);
    *p = 20;
    cout << *p << endl;
    unique_ptr<int> p2 = move(p);  // p释放为nullptr，只能移动
    cout << *p2 << endl;
}

void shared_ptrTest() {
    shared_ptr<int> p = make_shared<int>(10);
    shared_ptr<int> p2 = p;  // 拷贝，计数器变成2
    cout << p.use_count() << endl;

    p.reset();  // 释放内存，计数器变成1
    cout << p2.use_count() << endl;
}

void weak_ptrTest() {
    cout << "weak_ptrTest" << endl;
    shared_ptr<int> a = make_shared<int>(10);
    weak_ptr<int> b = a;  // 不影响引用计数
    cout << a.use_count() << endl;
    cout << b.use_count() << endl;
    a.reset();  // 释放内存，计数器变成0, b也变成nullptr
    // 使用前要检查对象是否还活着
    if (auto locked = b.lock()) {
        cout << *locked << endl;
    }
    else {
        cout << "对象已销毁" << endl;
    }
}

struct Resource {
    Resource() {
        cout << "构造\n";
    }
    ~Resource() {
        cout << "析构\n";
    }
};

void compare() {
    cout << "unique_ptrTest" << endl;
    {
        auto up = make_unique<Resource>();
        // 唯一指针，离开作用域，自动析构
    }
    // 共享指针
    cout << "shared_ptrTest" << endl;
    {
        auto sp = make_shared<Resource>();
        // 共享指针，离开作用域，引用计数减1
        cout << sp.use_count() << endl;
        {
            auto sp2 = sp;
            cout << sp2.use_count() << endl;
            // 离开作用域，引用计数减1
        }
        cout << sp.use_count() << endl;
    }
}


void process() {
    auto a = make_unique<int[]>(5);
    for (int i = 1; i <= 5; i++) {
        a[i] = i;
    }
    for (int i = 0; i < 5; i++) {
        cout << a[i] << endl;
    }
}


/*
面试题：unique_ptr 和 shared_ptr 的区别？什么时候用哪个？

参考：

所有权：unique_ptr 独占，shared_ptr 共享（引用计数）。

拷贝：unique_ptr 不可拷贝、只能移动；shared_ptr 可拷贝。

开销：unique_ptr 零开销（就一个裸指针）；shared_ptr 有引用计数开销（额外内存 + 原子操作）。

选择：默认用 unique_ptr（性能好、语义清晰）；只有确实需要多个持有者共享同一资源时才用 shared_ptr；需要观察但不拥有时用 weak_ptr。
*/

int main() {
    // unique_ptrTest();
    // shared_ptrTest();
    // weak_ptrTest();
    compare();
    process();
    return 0;
}