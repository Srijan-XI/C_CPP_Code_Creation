#include <iostream>

using namespace std;

class Distance {
private:
    int meters;

public:
    explicit Distance(int m) : meters(m) {}

    int getMeters() const {
        return meters;
    }

    void display() const {
        cout << "Distance: " << meters << " meters" << endl;
    }
};

int main() {
    Distance d1(10);
    d1.display();

    const Distance d3(15);
    d3.display();

    return 0;
}
