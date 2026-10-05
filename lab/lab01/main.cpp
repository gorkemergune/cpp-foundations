#include <iostream>
#include <vector>
using namespace std;


void swapTwoIntegers(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}



pair<int, int> findMinMax(int arr[], int size) {
    int min = arr[0], max = arr[0];

    for (int i = 1; i < size; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    return {min, max};
}



void reverse_array(int *arr, int size) {
    int start = 0;
    int end = size - 1;

    while (start < end) {
        swapTwoIntegers(arr[start], arr[end]);
        start++;
        end--;
    }
    for (int i = 0; i < size; i++)
    cout << arr[i] << " ";

}






int main() {

    int a = 5, b = 10;
    cout << "Before swapping: a = " << a << ", b = " << b << endl;
    swapTwoIntegers(a, b);
    cout << "After swapping: a = " << a << ", b = " << b << endl;

    vector<int> ARRAY = {5, 10, 15, 20, 25, 30, 35, 40, 45, 50};

    int size = 10;
    cout << "Elements in the array: " << ARRAY.size() << endl;

    pair<int, int> result = findMinMax(ARRAY.data(), size);
    cout << "Min and Max in the array: " << result.first << " " << result.second << endl;

    
    int myArr[10] = {1, 2, 5, 0, -1, 10, 20, 30, 40, 50};
    reverse_array(myArr, size);

    


    return 0;
}