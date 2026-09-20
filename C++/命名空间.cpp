// 命名空间：用于隔离命名空间，避免命名冲突
// 语法：namespace 命名空间名 { 函数、变量、类等 };


#include <iostream>
using namespace std;

namespace add_a {
    int add(int a, int b) {
        return a + b;
    }
}

namespace add_b {
    int add(int a, int b) {
        return a + b;
    }
}


int main() {
    std::cout << add_a::add(1, 2) << std::endl;
    std::cout << add_b::add(1, 2) << std::endl;
    return 0;
}
