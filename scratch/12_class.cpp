#include <iostream>
using namespace std;

class Triangle {
public:
    void triangle() {
        cout << "I'm a triangle" << endl;
    } 
};

class Isosceles : public Triangle {
public:
    void isosceles() {
        cout << "I'm an isosceles triangle" << endl;
    }
};

class Equilateral : public Isosceles {
public:
    void equilateral() {
        cout << "I'm an equilateral triangle" << endl;
    }
};

int main() {
    Equilateral obj;

    obj.triangle();
    obj.isosceles();
    obj.equilateral();

    return 0;
}