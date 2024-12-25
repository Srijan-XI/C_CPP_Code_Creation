#include <bits/stdc++.h>
using namespace std;

class Queue {
  int *arr;
  int start, end, currSize, maxSize;

public:
    Queue(int maxSize) {
        arr = new int[maxSize];
        start = -1;
        end = -1;
        currSize = 0;
        this->maxSize = maxSize; // Explicitly use `this` to avoid confusion
    }

    // Destructor to deallocate memory
    ~Queue() {
        delete[] arr;
    }

    void push(int newElement) {
        if (isFull()) {
            cout << "Queue is full\nExiting..." << endl;
            exit(1);
        }
        if (end == -1) {
            start = 0;
            end = 0;
        } else {
            end = (end + 1) % maxSize;
        }
        arr[end] = newElement;
        cout << "The element pushed is " << newElement << endl;
        currSize++;
    }

    int pop() {
        if (isEmpty()) {
            cout << "Queue Empty\nExiting..." << endl;
            exit(1);
        }
        int popped = arr[start];
        if (currSize == 1) {
            start = -1;
            end = -1;
        } else {
            start = (start + 1) % maxSize;
        }
        currSize--;
        return popped;
    }

    int top() {
        if (isEmpty()) {
            cout << "Queue is Empty" << endl;
            exit(1);
        }
        return arr[start];
    }

    int size() {
        return currSize;
    }

    // Added isEmpty function
    bool isEmpty() {
        return currSize == 0;
    }

    // Added isFull function (using currSize for clarity)
    bool isFull() {
        return currSize == maxSize;
    }
};

int main() {
    Queue q(6);
    q.push(4);
    q.push(14);
    q.push(24);
    q.push(34);

    cout << "The peek of the queue before deleting any element: " << q.top() << endl;
    cout << "The size of the queue before deletion: " << q.size() << endl;

    if (!q.isEmpty()) {
        cout << "The first element to be deleted: " << q.pop() << endl;
    }

    cout << "The peek of the queue after deleting an element: " << q.top() << endl;
    cout << "The size of the queue after deleting an element: " << q.size() << endl;

    return 0;
}