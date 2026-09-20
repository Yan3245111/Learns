#include <mutex>
#include <condition_variable>
#include <cstring>
#include <iostream>
#include <thread>
#include <queue>
using namespace std;


const int MAX_COUNT = 3;
mutex m;
condition_variable cv;
queue<int> q;


void producer() {
    for (int i = 1; i <= 10; i++) {
        unique_lock<mutex> lock(m);
        cv.wait(lock, [] {return q.size() < MAX_COUNT;});
        q.push(i);
        cout << "producer produce: " << i  << "\n" << endl;
        lock.unlock();
        cv.notify_one();
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}


void consumer() {
    for (int i = 1; i <= 10; i++) {
        unique_lock<mutex> lock(m);
        cv.wait(lock, [] {return !q.empty();});
        int val = q.front();
        cout << "consumer consume: " << val  << "\n" << endl;
        q.pop();
        lock.unlock();
        cv.notify_one();
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}


int main() {
    thread t1(producer);
    thread t2(consumer);
    t1.join();
    t2.join();
    return 0;
}