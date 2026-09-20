// 线程池思想：不要为每个任务创建一个线程，而是预先创建固定数量的线程，让它们循环从任务队列里取任务执行


// 完整实现
#include <iostream>
#include <thread>
#include <mutex>               // 互斥锁，用于保护共享资源
#include <queue>
#include <condition_variable>  // 条件变量，用于线程等待
#include <functional>          // 函数对象，用于存储任务
#include <vector>
#include <future>              // 异步任务
#include <atomic>              // 原子操作，用于线程安全
using namespace std;


class ThreadPool {
private:
    bool stop;
    vector<thread> workers;
    queue<function<void()>> tasks;  // 任务队列
    mutex mtx;
    condition_variable cv;
    void workerLoop() {
        function<void()> task;
        {
            unique_lock<mutex> lock(mtx);
            cv.wait(lock, [this] {return stop || !tasks.empty();});  // 等待stop是true并且任务队列不为空
            if (stop && tasks.empty()) return;
            task = move(tasks.front());
            tasks.pop();
        }
        task();
    }
public:
    explicit ThreadPool(size_t numThreads) : stop(false) {
        // 创建线程
        for (size_t i = 0; i < numThreads; i++) {
            workers.emplace_back([this] {  // 在尾部构造一个元素
                workerLoop();
            });
        }
    }
    ~ThreadPool() {
        { unique_lock<mutex> lock(mtx);
         stop = true;
        }
        cv.notify_all();
        for (auto& t: workers) {
            if (t.joinable()) t.join();
        }
    }
    template <typename F, typename... Args>
    auto submit(F&& f, Args&&... args) -> future<typename result_of<F(Args...)>::type> {
        using ReturnType = typename result_of<F(Args...)>::type;
        auto task = make_shared<packaged_task<ReturnType()>>(bind(forward<F>(f), forward<Args>(args)...));
        future<ReturnType> res = task->get_future();
        {
            unique_lock<mutex> lock(mtx);
            if (stop) throw runtime_error("ThreadPool is stopped");
            tasks.emplace([task] {(*task)();});
        }
        cv.notify_one();
        return res;
    }
}; 


int main() {
    ThreadPool pool(4);   // 4 个工作线程

    vector<future<int>> results;
    for (int i = 0; i < 10; i++) {
        results.emplace_back(
            pool.submit([i] {
                this_thread::sleep_for(chrono::milliseconds(100));
                cout << "任务 " << i << " 在线程 "
                     << this_thread::get_id() << " 执行\n";
                return i * i;
            })
        );
    }

    for (auto& r : results) {
        cout << "结果: " << r.get() << endl;   // 获取每个任务的返回值
    }
    return 0;
}