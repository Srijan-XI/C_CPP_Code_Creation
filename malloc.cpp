#include <iostream>
#include <cstdlib>
using namespace std;

class MyClass {
public:
    int x;
    MyClass() : x(0) { 
        cout << "Constructor called\n"; 
    }
    ~MyClass() { 
        cout << "Destructor called\n"; 
    }
};

int main() {
   
    MyClass* obj = (MyClass*)malloc(sizeof(MyClass));
    obj->x = 10;
    cout << "x = " << obj->x << "\n";

   
    obj->~MyClass();

    
    free(obj);

    return 0;
}