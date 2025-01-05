#include <iostream>
#include <vector>

using namespace std;

void insert_element(vector<int>& arr, int element, int position = -1) {
    if (position == -1) {
        arr.push_back(element);
    } 
    else if (position >= 0 && position <= arr.size()) {
        arr.insert(arr.begin() + position, element);
    } 
    else {
        cout << "Invalid position " << endl;
    }
}

int main() {
    vector<int> arr = {1, 2, 3};
    
    insert_element(arr, 4);
    insert_element(arr, 5, 1);
    
    for (int num : arr) {
        cout << num << " ";  
    }
    cout << endl;

    return 0;
}
