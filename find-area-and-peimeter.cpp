//code in which user give input to find area and perimeter
#include <iostream>

using namespace std;

int main() {
 double l,b ;
 cout << "Enter the length of the rectangle: ";
    cin >> l;

    cout << "Enter the width of the rectangle: ";
    cin >> b;

    double a = l * b , p = 2*(l+b);


    cout << "The area of the rectangle is: " << a << endl;
 cout << "The perimeter of the rectangle is: " << p << endl;

if (a>p){
    cout<<"area is greater than perimeter" <<endl;
}


}
