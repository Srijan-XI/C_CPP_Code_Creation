#include <iostream>

using namespace std;

class MyClass {
public:
    int data;

    MyClass(int d) : data(d) {}
};

int main() {
    MyClass obj1(10);
    MyClass obj2 = obj1; // Shallow copy

    // Get pointers to the data members of obj1 and obj2
    int* ptr1 = &obj1.data;
    int* ptr2 = &obj2.data;

    // Check if the pointers are the same
    if (ptr1 == ptr2) {
        cout << "obj1.data and obj2.data are in the same memory location" << endl;
    } else {
        cout << "obj1.data and obj2.data are in different memory locations" << endl;
    }

    return 0;
}