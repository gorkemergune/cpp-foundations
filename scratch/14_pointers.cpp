#include <iostream>

int reverse_arr(int *arr) {

    int *p = arr;
    int count = 0;
    while (*p) {
        count++;
        p++;
    }

    while (arr < p) {
        int temp = *arr;
        *arr = *p;
        *p = temp;
        arr++;
        p--;
    }

    return 0;
}


int main() {

    int arr[] = {1, 2, 3, 4, 5, 0};
    reverse_arr(arr);
    for (int i = 0; i < 5; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;



}