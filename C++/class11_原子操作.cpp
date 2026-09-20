// 无所的线程安全 atomic，抱闸一个操作不被其他线程中断
#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
#include <queue>
#include <condition_variable>
#include <mutex>
using namespace std;


atomic<int> counter(0);  // 原子整数，初始值为0


// atomic 是cpu原子指令，和加锁是一样的效果，开销更小不阻塞，而且速度更快
void increment() {
    for (int i = 0; i < 1000000; i++) {
        counter++;
    }
}


// 常见的atomic用法
void test_atomic() {
    atomic<int> a(0);
    atomic<bool> b(false);
    atomic<long> c(0);
    atomic<double> d(0.0);  // double的原子操作有限，不建议使用
    // 基本操作
    a.store(10);  // 原子写，等价于a=10
    int v = a.load();  // 原子读，等价于v=a
    a++;
    a--;
    a += 5;

    int expected = 10;
    // 原子交换比较，如果a等于expected，就将a设置为20，并返回true，否则把expected设置为a的值，返回false
    bool ok = a.compare_exchange_strong(expected, 20); 
}

// atomic 只能保护单个变量的单词 操作，如果有多个变量，就不够用了，比如下面，所以不可代替mutex，单个变量操作可以使用atomic
atomic<int> a(0), b(0);


void test_atomic2() {
    a++;
    b++;
    // 别的线程可能看到a=1, b=0
}


// 实际应用：线程停止标志，因为2个线程同时读写stopFlag，所以要使用atomic来保护stopFlag，如果主线程不读取，可以不使用atomic，直接使用bool
atomic<bool> stopFlag(false);


void worker() {
    int count = 0;
    while (!stopFlag.load()) {
        count++;
        this_thread::sleep_for(chrono::milliseconds(100));
        cout << "worker count = " << count  << "\n" << endl;
        if (count >= 10) {
            stopFlag = true;
        }
    }
}


void listener() {
    thread t1(worker);
    while (!stopFlag.load()) {
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    t1.join();
    cout << "listener stop" << endl;
}


// 生产消费者: 生产者生产数据，消费者消费数据，生产者和消费者通过条件变量和互斥锁来协调
// 比如queue轮询的时候，消费者线程空转，浪费资源
// 理想状态：队列空时，消费者睡眠等待，生产者生产数据后，消费者唤醒消费消费数据
mutex mtx;
condition_variable cv;
queue<int> q;
const int MAX_SIZE = 5;


// 如果消费者消费数据快，生产者生产数据慢，队列会满，生产者会等待消费者消费数据
// 如果生产者生产数据快，消费者消费数据慢，队列会空，消费者会等待生产者生产数据
void producer() {
    for (int i = 1; i <= 10; i++) {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [] {return q.size() < MAX_SIZE;});  // 等待消费者纳州书局，队列变小，生产者才被唤醒开始塞数据
        q.push(i);
        cout << "生产者放入: " << i << "，队列大小: " << q.size() << endl;
        lock.unlock();
        cv.notify_one();  // 通知一个等待的消费者
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}


void consumer() {
    for (int i = 1; i <= 10; i++) {
        unique_lock<mutex> lock(mtx);
        // 队列空，睡眠，等待生产者生产
        cv.wait(lock, [] {return !q.empty();});
        int v = q.front();
        q.pop();
        cout << "消费者取出: " << v << "，队列大小: " << q.size() << endl;
        lock.unlock();
        cv.notify_one();  // 通知一个等待的生产者
        this_thread::sleep_for(chrono::milliseconds(150));
    }
}


// 简单异步
#include <future>


int compute(int x) {
    this_thread::sleep_for(chrono::milliseconds(1000));
    return x * x;
}


int async_compute() {
    // 异步启动任务
    future<int> fut = async(launch::async, compute, 5);
    int result = fut.get();
    cout << "异步计算结果: " << result << endl;
    return result;
}


// 常用的异步操作
void async_operate() {
    async(launch::async, compute, 3);   // 强制在新线程运行, 第二个参数为function，可以跟参数
    async(launch::deferred, compute, 3);   // 延迟到调用get时再运行
}


// promise和future  promise是生产者，future是消费者，适合手写异步通信
void setValue(promise<int> p) {
    p.set_value(100);
}


void getValue() {
    promise<int> p;
    future<int> f = p.get_future();
    thread t(setValue, move(p));  // p不可拷贝，只能移动
    cout << "getValue: " << f.get() << endl;
    t.join();
}

/*
async / thread 怎么选？
thread	async
粒度	底层，手动管理	高层，自动管理
拿返回值	麻烦，要手动同步	直接用 future.get()
异常传播	需要自己处理	异常通过 future 传播
适用	长期运行、需要精细控制	一次性任务、需要返回值
结论：需要结果时，用async，需要长期运行时，用thread
*/


/*
面试题：std::atomic 的底层原理是什么？它能替代 mutex 吗？

参考：

原理：atomic 通过 CPU 提供的原子指令（如 x86 的 lock 前缀指令、ARM 的 exclusive 指令）实现。
这些指令保证读-改-写在硬件层面不被其他核心打断，且提供内存序保证（可见性）。所以不需要操作系统锁，开销极小。

能否替代 mutex：不能。atomic 只能保证单个变量的单次操作原子性。
如果需要：①保护多个变量的联动；②保护一段代码；③实现复合操作（如"检查后修改"），仍然要用 mutex。atomic 适合计数器、标志位等简单场景。

补充：atomic 的 CAS 操作（compare_exchange）可以用来实现无锁数据结构，但难度高、易错，实际项目优先用成熟的库。

*/


int main() {
    // thread t1(increment);
    // thread t2(increment);
    // t1.join();
    // t2.join();
    // cout << "counter = " << counter << endl;

    // test_atomic();
    // listener();

    // 生产者消费者
    // thread t1(producer);
    // thread t2(consumer);
    // t1.join();
    // t2.join();
    // cout << "生产者消费者结束" << endl;

    // 异步计算
    // async_compute();

    // 异步操作
    getValue();

    return 0;
}