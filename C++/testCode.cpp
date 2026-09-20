#include <map>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <chrono>
#include <sstream>
using namespace std;


void testCode() {
    const int N = 100e4;
    // map 插入
    auto start = chrono::high_resolution_clock::now();
    map<int, int> mp;
    for (int i = 0; i < N; i++) {
        mp[i] = i;
    }
    auto end = chrono::high_resolution_clock::now();
    cout << "map insert time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl;
    // 哈希map插入
    start = chrono::high_resolution_clock::now();
    unordered_map<int, int> ump;
    for (int i = 0; i < N; i++) {
        ump[i] = i;
    }
    end = chrono::high_resolution_clock::now();
    cout << "unordered_map insert time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl;
}


void testCode1() {
    string test = "apple banana apple cherry banana apple";
    unordered_map<string, int> mp;
    istringstream iss(test);
    string word;
    // iss >> word 会自动跳过空格，读取一个单词
    while (iss >> word) {
        mp[word]++;
    }
    for (const auto& [w, count] : mp) {
        cout << w << " " << count << endl;
    }
}


vector<int> testCode2() {
    vector<int> nums = {2, 3, 7, 9, 10, 12};
    unordered_map<int, int> mp;
    for (int i = 0; i < nums.size(); i++) {
        // 当前数值为nums[i]，所以要找的值为9 - nums[i]，如果存在，就返回当前索引和存在索引
        int res = 9 - nums[i];
        if (mp.count(res)) {
            return {mp[res], i};
        }
        mp[nums[i]] = i;
    }
    return {};
}


int main() {
    // testCode();
    // testCode1();
    vector<int> res = testCode2();
    for (auto x: res) {
        cout << x << endl;
    }
}   