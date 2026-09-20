#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
// 只关心查找，不关心速度可以用哈希unordered_map，用法和map一致，查找速度更快，遍历的时候是随机的
using namespace std;


// 序列 == python list
void VectorTest() {
    vector<int> v1;
    // 增加元素
    v1.push_back(1);
    v1.push_back(2);
    // 访问元素
    cout << v1[0] << endl;
    // 遍历
    for (auto x: v1) {
        cout << "遍历 " << x << endl;
    }
    // 改
    v1[0] = 100;
    // 插入
    v1.insert(v1.begin(), 0);
    v1.insert(v1.begin() + 1, 1);  // 索引1处插入2
    // 删除元素
    v1.pop_back();  // 删除最后一个元素
    v1.erase(v1.begin() + 1);  // 删除索引1处的元素
    cout << v1.size() << endl;
    // 清空容器
    v1.clear();
    cout << v1.size() << endl;
}


// 映射 == python dict 
void MapTest() {
    // 有序字典, 会按照key的大小排序
    map<string, int> mp;
    // 增加
    mp["a"] = 1;
    mp["b"] = 2;
    mp["c"] = 3;
    // 插入
    mp.insert({"d", 4});
    mp.emplace("e", 5);
    // 查
    cout << mp["a"] << endl;
    cout << mp["b"] << endl;

    // 改
    mp["a"] = 100;
    cout << mp["a"] << endl;
    // 删除
    mp.erase("a");
    cout << mp["a"] << endl;  // 访问不存在的元素会自动创建，默认值为0
    // 遍历 如果使用auto& x, 则x是引用类型, 可以直接修改元素，现在是拷贝，更改x的值不影响原mp
    for (auto x: mp) {
        cout << x.first << " " << x.second << endl;
    }
    // 显式遍历，也是拷贝pair<const string, int>& x: mp 是指针引用
    for (pair<const string, int> x: mp) {
        cout << x.first << " " << x.second << endl;
    }
    // 推荐写法 const表示只读，去掉const可修改
    for (const auto& [key, value]: mp) {
        cout << key << " " << value << endl;
    }
}


int main() {
    // VectorTest();
    MapTest();
}