#include <vector>
#include <iostream>
using namespace std;


class Student {
private:
    string name;
    static vector<string> allNames;
public:
    Student(string n) : name(n) {
        allNames.push_back(n);
    }
    static void printAll() {
        for (const string& name: allNames) {
            cout << name << " ";
        }
        cout << endl;
    }
    static int getAll() {
        return allNames.size();
    }
};

vector<string> Student::allNames;


int main() {
    Student s1("张三");
    Student s2("李四");
    Student s3("王五");
    Student::printAll();
    cout << "all count: " << Student::getAll() << endl;
    return 0;
}
