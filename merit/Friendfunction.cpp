#include <iostream>

class MyClass {
private:
    int privateData;

public:
    MyClass(int data){
        
        privateData=data; 
        
        }

    friend void printPrivateData(MyClass& obj); 
 // Declaration of friend function
};

void printPrivateData(MyClass& obj) {
    std::cout << "Private data: " << obj.privateData << std::endl;
}

int main() {
    MyClass obj(10);
    printPrivateData(obj); // Calling the friend function
    return 0;
}