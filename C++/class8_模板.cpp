// 模板的作用：可以实现代码的复用
/*
举例说明：求两个数较大值
*/

#include <string>
#include <iostream>
using namespace std;

// 不同数据类型要写三个不同的函数
int maxInt(int a, int b) {return a > b ? a : b;}
double maxDouble(double a, double b) {return a > b ? a : b;}
string maxString(const string& a, const string& b) {return a > b ? a : b;}
// 使用模板就可以解决这个问题 T的话可以是任意类型，包括int、double、string等，但是ab数据类型必须相同
template <typename T>
T myMax(T a, T b) {
    return a > b ? a : b;
}


// 也可以不同
template <typename T1, typename T2>
auto max1(T1 a, T2 b) {
    return a > b ? a : b;
}


// 模板类
template <typename T>
class MyArray {
    T* data;
    int size;
public:
    MyArray(int n): size(n), data(new T[n]) {}
    ~MyArray() {delete[] data;}
    // 重载下标运算符，实现数组的访问
    T& operator[](int i) {return data[i];}
    int data_size() const {return size;}
};


// thingkcode 写一个函数模板 T arrayMax(T arr[], int n)，返回数组中的最大元素。用 int 数组和 double 数组各测试一次。
template <typename T>
T arrayMax(T arr[], int n) {
    T max_t = arr[0];
    for (int i = 1; i < n; i++) {
        max_t = max_t > arr[i] ? max_t : arr[i];
    }
    return max_t;
}

/*
面试题：模板的实例化发生在编译期还是运行期？这带来什么优缺点？

参考：

编译期。编译器在编译时为每个用到的类型生成一份具体代码。

优点：①运行时零开销（没有虚函数那样的动态派发）；②类型安全，编译期就能查错。

缺点：①代码膨胀——每个类型生成一份，二进制变大；②编译时间变长；③错误信息难读（模板报错通常很长）。

对比：虚函数是运行期多态（动态绑定），模板是编译期多态（静态绑定）。
*/


int main() {
    // cout << myMax(1, 2) << endl;
    // cout << myMax(1.0, 2.0) << endl;
    // cout << myMax("a", "b") << endl;
    // MyArray<int> a(5);
    // a[0] = 1;
    // cout << a[0] << endl;
    // MyArray<double> b(5);
    // b[0] = 1.0;
    // cout << b[0] << endl;
    // MyArray<string> c(5);
    // c[0] = "a";
    // cout << c[0] << endl;
    int a[] = {1, 2, 3, 4, 5};
    cout << arrayMax(a, 5) << endl;
    double b[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    cout << arrayMax(b, 5) << endl;
}