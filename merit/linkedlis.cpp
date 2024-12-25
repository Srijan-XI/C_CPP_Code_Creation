#include <iostream>
#include <vector>
using namespace std;
class Node{
    public: // access modifier
    int data; // the data value
    Node* next; // the pointer to the next value
    public:
    // constructor
    
    Node (int data1){
        data=data1;  // Initialize data with the provided value
        next=nullptr;  // Initialize next as null since it's the end of the list
        cout<<"next"<<next<<endl;
        cout<<"data"<<data<<endl;

    }
};
int main(){
    vector<int> arr={2,5,8,7};
    Node* y= new Node(arr[0]);
    cout<<y<<'\n'; // returns the memory value
    cout<<y->data<<'\n'; // returns the data stored at that memory point
}