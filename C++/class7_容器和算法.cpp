/*
vector 和 list<int> 区别
vector 是连续存储的，随机访问复杂度为 O(1)，尾部插入复杂度均摊为 O(1)， 中间插入复杂度为 O(n)。
list 是链表存储的，随机访问复杂度为 O(n)，尾部插入复杂度为 O(1)， 中间插入复杂度为 O(1)。
默认都是用vector，因为vector 更高效，只有频繁中间插入、删除时且不需要随机访问时，才用list。
*/
#include <map>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;


void vectorTest() {
    vector<int> v;  // 创建空
    vector<int> v1 = {1, 2, 3}; // 创建并初始化
    vector<int> v2(5, 10);  // 创建5个10
    vector<int> v3(5);      // 创建5个0
    // 增
    v.push_back(1);  // 尾部插入
    v.push_back(2);
    v.insert(v.begin(), 0);  // 头部插入()
    v.insert(v.begin() + 3, 3);  // 索引3插入3  -> 0, 1, 2, 3
    // 改
    v[0] = 100;
    v.at(0) = 200;
    // 查
    cout << "查：" << endl;
    cout << v.front() << endl;
    cout << v.back() << endl;
    cout << v.size() << endl;
    cout << v.capacity() << endl;
    cout << v.empty() << endl;
    cout << v[1] << endl;

    // 遍历 三种方式
    cout << "遍历：" << endl;
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << endl;
    }
    cout << "遍历1：" << endl;
    for (int x: v) {
        cout << x << endl;
    }
    // begin end是迭代器 可以使用上一个下一个
    cout << "遍历2：" << endl;
    for (auto it = v.begin(); it != v.end(); it++) {
        cout << *it << endl;
    }
    // 删
    v.pop_back();  // 尾部删除
    v.erase(v.begin());  // 头部删除
    v.erase(v.begin() + 1);  // 索引1删除 -> 1
    v.clear();  // 清空
}


// 常用算法
void algo_test() {
    vector<int> v = {3, 1, 2, 5, 6, 4};
    // 排序
    sort(v.begin(), v.end());  // 升序
    sort(v.begin(), v.end(), greater<int>());  // 降序
    // 查找3
    auto it = find(v.begin(), v.end(), 3);
    if (it != v.end()) {
        cout << "找到3" << endl;
    } else {
        cout << "未找到3" << endl;
    }
    // 统计3出现的次数
    int n = count(v.begin(), v.end(), 3);
    cout << "3出现的次数为：" << n << endl;
    // 条件统计
    int evenCount = count_if(v.begin(), v.end(), [](int x) {return x % 2 == 0;});
    cout << "偶数的个数为：" << evenCount << endl;
    // 最值
    auto maxIt = max_element(v.begin(), v.end());
    cout << "最大值为：" << *maxIt << endl;
    auto minIt = min_element(v.begin(), v.end());
    cout << "最小值为：" << *minIt << endl;
    // 反转
    reverse(v.begin(), v.end());
    // 去重 必须先排序
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
}


void map_test() {
    // 创建
    map<string, int> m;
    // 增/改
    m["a"] = 1;
    m["b"] = 2;
    m["c"] = 3;
    m.insert({"d", 4});
    // 查
    if (m.count("a")) {
        cout << "a的值为：" << m["a"] << endl;
    }
    auto it = m.find("a");  // 返回迭代器
    if (it != m.end()) {
        cout << it->first << ": " << it->second << endl;
    }
    // 遍历
    cout << "遍历：" << endl;
    for (const auto& p: m) {
        cout << p.first << ": " << p.second << endl;
    }
    // 删
    m.erase("a");
    // 判断
    cout << m.size() << " " << m.empty() << endl;
    // 清空
    m.clear();
}

// thinking: vector<int> v = {5, 2, 8, 1, 9, 2, 4};
void thinkCode() {
    vector<int> v = {5, 2, 8, 1, 9, 2, 4};
    // 排序
    sort(v.begin(), v.end());
    cout << "排序后：" << endl;
    // 引用 零拷贝 一定记得使用引用打印
    for (const int& x: v) {
        cout << x << endl;
    }
    // find 8
    auto it = find(v.begin(), v.end(), 8);
    if (it != v.end()) {
        cout << "找到8" << endl;
    } else {
        cout << "未找到8" << endl;
    }
    // 统计偶数个数
    int evenCount = count_if(v.begin(), v.end(), [](int x) {return x % 2 == 0;});
    cout << "偶数的个数为：" << evenCount << endl;
}


int main() {
    // vectorTest();
    // algo_test();
    // map_test();
    thinkCode();
    return 0;
}