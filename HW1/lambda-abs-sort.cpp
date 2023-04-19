#include <iostream>
#include <algorithm>
#include <cmath>

int main() {
    int arr[] = {-1,1,10,-10,8,9,-9,2023,-1945};
    int n = sizeof(arr) / sizeof(arr[0]);

    std::sort(arr, arr + n, [](int a, int b) { return std::abs(a) < std::abs(b); });

    for (int i = 0; i < n; ++i) {
        std::cout << arr[i] << ' ';
    }

    return 0;
}
