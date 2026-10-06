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



bool isPalindrome(const string &str) {
    int left = 0;
    int right = str.length() - 1;

    while (left < right) {
        if (str[left] != str[right]) {
            return false;
        }
        left++;
        right--;
    }

    return true;
}



double average(const vector<int> &arr) {
    if (arr.empty()) {
        return 0.0;
    }

    double sum = 0.0;
    for (int num : arr) {
        sum += num;
    }

    return sum / arr.size();
}


vector<int> removeDuplicates(const vector <int> &arr) {
    vector<int> uniqueArr;
    for (int num : arr) {
        if (find(uniqueArr.begin(), uniqueArr.end(), num) == uniqueArr.end()) {
            uniqueArr.push_back(num);
        }
    }
    return uniqueArr;
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

    string myString = "racecar";
    cout << "\nIs the string \"" << myString << "\" a palindrome? " << (isPalindrome(myString) ? "Yes" : "No") << endl;

    double avg = average(ARRAY);
    cout << "Average of the array: " << avg << endl;
    cout << "Elements greater than the average: "; 
    for (int num : ARRAY) {
        if (num > avg) {
            cout << num << " ";
        }
    } cout << endl;



    return 0;
}