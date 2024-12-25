#include <iostream>  
using namespace std;  
class Opp { 
 public:
 int a;  
 int b; 
 int z;  
  Opp() { 
    
 } 
 void input(int x, int y, int l) { 
    a=x;  
    b=y;  
    z=l;  
 } 
 void display() { 
 cout<<"value of a:" <<a<<endl;  
 cout<<"value of b:" <<b<<endl;  
 cout<<"value of z:" <<z<<endl;  
 } 
}; 
 
int main()  {  
 Opp obj1;  
 obj1.input(4,8,12);  
 Opp obj2(obj1); 
 obj1.display();
 cout<<"---------------\n"; 
 obj2.display(); 
 return 0;  
}  