#include <vector>
#include <mutex>
#include <thread>
#include <iostream>
using namespace std;


void hello() {
    cout << "子线程：Hello, World!" << endl;
}


// 并发测试
int count = 0;


void test_increament() {
    for (int i = 0; i < 1000000; i++) {
        count++;
    }
}


// 互斥锁 同一时刻只能有一个线程访问
 mutex m;
 int count1 = 0;


 void test_increament_mutex() {
    for (int i = 0; i < 100e4; i++) {
        lock_guard<mutex> lock(m);
        count1++;
    }
 }

 
 // 锁讲解
 /*
 lock_guard:最简单的锁管理器，构造时加锁，析构时自动解锁，作用域结束自动解锁。
 不可复制，不能提前手动解锁，不能加延迟所

 unique_lock: 更灵活，需要维护锁的状态，可手动解锁，加锁
 */

void test_unique_lock() {
    unique_lock<mutex> lock(m);  // 构造会自动加锁，不可二次lock，会报错
    lock.unlock();
    lock.lock();
    lock.unlock();
    // 构造不加锁
    unique_lock<mutex> lock2(m, defer_lock); // 延迟加锁，需要手动调用lock()加锁
    lock2.lock();
    lock2.unlock();  // 如果忘记unlock可能会死锁，程序崩溃等
}


// 死锁 两个线程各持有一把锁，又想拿对方的所，就会互相等待，永久卡住，解决办法，一次性锁多把
mutex m1, m2;


void test_deadlock() {
    lock(m1, m2);
    lock_guard<mutex> lock1(m1, adopt_lock);
    lock_guard<mutex> lock2(m2, adopt_lock);
    // 或者使用c++17
    // scoped_lock lock(m1, m2);
    // 执行代码
}


void f(int a, int b) {
    cout << "f(" << a << ", " << b << ")" << endl;
}


// 线程常用操作
void test_thread() {
    thread t1(hello);  // 创建线程，执行hello函数
    thread t2(f, 1, 2);  // 创建线程，执行hello函数，传递参数
    t1.join();    // 等待结束 会阻塞主线程 分离线程必须2选1
    t2.detach();  // 分离线程，运行在主线程后台，不会阻塞主线程，主程序退出时被os回收
    t2.joinable();  // 检查线程是否可join

    unsigned n = thread::hardware_concurrency();  // 获取硬件并发数，0表示不支持

    std::thread::id tid = this_thread::get_id();  // 获取当前线程ID 不可以转数据类型
    this_thread::sleep_for(chrono::seconds(1));  // 等待1秒
}


// thinking 写一个多线程，启动3个线程，使用mutex保护，每个线程增加到1000000
int count2 = 0;
mutex m3;


void test_increament_mutex3() {
    for (int i = 0; i < 100e4; i++) {
        lock_guard<mutex> lock(m3);
        count2++;
    }
}

// thinking2 两个线程，一个不断在vector里添加元素，一个不断读取size，是否安全？
// 不安全，因为vector是线程不安全的，读size也会影响push_back操作，解决加一个mutex保护，都用同一把锁操作
vector<int> v;
void test_vector() {
    for (int i = 0; i < 10000; i++) {
        v.push_back(i);
    }
}


void test_vector_size() {
    for (int i = 0; i < 10000; i++) {
        cout << v.size() << endl;
    }
}


/*
面试题：什么是竞态条件？如何避免？

参考：

竞态条件：多个线程并发访问共享数据，且至少有一个是写操作，最终结果依赖线程执行的时序，
不可预测。根本原因是某些操作（如 counter++）在底层是多步的，线程交错执行会互相干扰。

避免方法：①用 mutex 保护临界区；②用原子操作 std::atomic（针对简单变量，无锁）；③避免共享数据（每个线程用独立数据，最后合并）；④用不可变数据。

其中"避免共享"是最高效的，因为锁有性能开销。面试可以提一句："能不用锁就不用锁，优先考虑减少共享。"
*/

int main() {
    thread t1(test_vector);
    thread t2(test_vector_size);
    t1.join();
    t2.join();
    return 0;
}



// int main() {
//     thread t1(test_increament_mutex3);
//     thread t2(test_increament_mutex3);
//     thread t3(test_increament_mutex3);
//     t1.join();
//     t2.join();
//     t3.join();
//     cout << "count2 = " << count2 << endl;
//     return 0;
// }


// int main1() {
//     // 创建第一个线程
//     thread t(hello);
//     t.join();
//     cout << "主线程：Hello, World!" << endl;
//     // 并发测试 按道理应该为2000000，实际1069775，说明并发测试中，线程之间的通信和同步问题需要考虑，同时读写问题
//     thread t1(test_increament);
//     thread t2(test_increament);
//     t1.join();
//     t2.join();
//     cout << "count = " << count << endl;
//     // 互斥锁测试
//     thread t3(test_increament_mutex);
//     thread t4(test_increament_mutex);
//     t3.join();
//     t4.join();
//     cout << "count1 = " << count1 << endl;
//     // unique_lock测试
//     test_unique_lock();
// }
