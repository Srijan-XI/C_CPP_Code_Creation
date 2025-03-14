#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Combinatorics {
private:
    vector<string> elements;

public:
    Combinatorics(const vector<string>& elems) : elements(elems) {}

    void printCombination(vector<string>& data, int start, int end, int index, int r) {
        if (index == r) {
            for (int j = 0; j < r; j++)
                cout << data[j] << " ";
            cout << endl;
            return;
        }

        for (int i = start; i <= end && end - i + 1 >= r - index; i++) {
            data[index] = elements[i];
            printCombination(data, i + 1, end, index + 1, r);
        }
    }

    void findPermutations() {
        sort(elements.begin(), elements.end());
        cout << "Possible permutations are:\n";
        do {
            for (const auto& str : elements)
                cout << str << " ";
            cout << endl;
        } while (next_permutation(elements.begin(), elements.end()));
    }

    void generateCombinations(int r) {
        vector<string> data(r);
        printCombination(data, 0, elements.size() - 1, 0, r);
    }
};

int main() {
    int choice;
    int n;
    vector<string> userElements;

    cout << "Enter the number of elements: ";
    cin >> n;

    cout << "Enter the elements:\n";
    for (int i = 0; i < n; i++) {
        string element;
        cin >> element;
        userElements.push_back(element);
    }

    Combinatorics combinatorics(userElements);

    cout << "Choose an option:\n1. Permutation\n2. Combination\n";
    cin >> choice;

    if (choice == 1) {
        combinatorics.findPermutations();
    } else if (choice == 2) {
        int r;
        cout << "Enter the size of combinations: ";
        cin >> r;

        if (r > n || r <= 0) {
            cout << "Invalid combination size!" << endl;
        } else {
            combinatorics.generateCombinations(r);
        }
    } else {
        cout << "Invalid choice!" << endl;
    }

    return 0;
}
