#include <iostream>
#include <vector>
using namespace std;



int main() {


    vector<int> ARRAY = {5, 10, 15, 20};
    
    vector<int> myVector(ARRAY.begin(), ARRAY.end());
    vector<int> myVector2 = {5, 10, 15, 20};
    int size;
    cin >> size;

    int myArr[size];

    ARRAY.resize(size);

    

    

}