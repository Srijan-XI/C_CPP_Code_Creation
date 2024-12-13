#include <iostream>
using namespace std;

class shape {
public:
    string name;
    int sides;

    shape(string name, int sides) {
        this->name = name;
        this->sides = sides;
    }
};

class triangle : public shape {
private:
    int base, height;

public:
    triangle(string name, int sides, int base, int height) : shape(name, sides) {
        this->base = base;
        this->height = height;
    }

    void area() {
        cout << "Area of triangle: " << (0.5 * base * height) << endl;
    }

    void details() {
        cout << "Shape is: " << name << endl;
        cout << "Number of sides are: " << sides << endl;
        cout << "Base is: " << base << endl;
        cout << "Height is: " << height << endl;
        area();
    }
};

class square : public shape {
private:
    int side;

public:
    square(string name, int sides, int side) : shape(name, sides) {
        this->side = side;
    }

    void area() {
        cout << "Area of square: " << (side * side) << endl;
    }

    void details() {
        cout << "Shape is: " << name << endl;
        cout << "Number of sides are: " << sides << endl;
        cout << "Side is: " << side << endl;
        area();
    }
};

int main() {
    string shapeName;
    int sides, base, height, side;

    cout << "Enter shape name (triangle or square): ";
    cin >> shapeName;

    if (shapeName == "triangle") {
        cout << "Enter number of sides, base, and height: ";
        cin >> sides >> base >> height;
        triangle t(shapeName, sides, base, height);
        t.details();
    } else if (shapeName == "square") {
        cout << "Enter number of sides and side length: ";
        cin >> sides >> side;
        square s(shapeName, sides, side);
        s.details();
    } else {
        cout << "Invalid shape name." << endl;
    }

    return 0;
}
