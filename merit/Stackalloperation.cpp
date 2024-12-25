#include <bits/stdc++.h>
using namespace std;

class Stack {
  int size;
  int *arr;
  int top;
public:
  Stack() {
    top = -1;
    size = 1000;
    arr = new int[size];
  }

  // Existing operations (unchanged):
  void push(int x) {
    top++;
    arr[top] = x;
  }

  int pop() {
    int x = arr[top];
    top--;
    return x;
  }

  int Top() {
    return arr[top];
  }

  int Size() {
    return top + 1;
  }

  // Additional operations:
  bool isEmpty() {
    return top == -1;
  }

  bool isFull() {
    return top == size - 1;
  }

  int peek(int index) {
    if (index < 0 || index > top) {
      return -1; // Or handle the error appropriately
    }
    return arr[index];
  }

  void clear() {
    top = -1;
  }
};

int main() {
  Stack s;
  s.push(6);
  s.push(3);
  s.push(7);

  cout << "Top of stack is before deleting any element " << s.Top() << endl;
  cout << "Size of stack before deleting any element " << s.Size() << endl;

  // Utilize existing operations for stack manipulation:
  int deletedElement = s.pop();

  cout << "The element deleted is " << deletedElement << endl;
  cout << "Size of stack after deleting an element " << s.Size() << endl;
  cout << "Top of stack after deleting an element " << s.Top() << endl;

  // Demonstrate additional operations:
  cout << "Is the stack empty? " << (s.isEmpty() ? "Yes" : "No") << endl;
  cout << "Is the stack full? " << (s.isFull() ? "Yes" : "No") << endl;
  cout << "Element at index 1: " << s.peek(1) << endl;

  s.clear();
  cout << "Stack after clearing: " << (s.isEmpty() ? "Empty" : "Not empty") << endl;

  return 0;
}