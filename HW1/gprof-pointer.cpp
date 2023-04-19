#include <iostream>
#include <memory>

int sum_elements_raw(int* arr, size_t size) {
    int sum = 0;
    for (size_t i = 0; i < size; ++i) {
        sum += arr[i];
    }
    return sum;
}

int sum_elements_smart(std::unique_ptr<int[]> arr, size_t size) {
    int sum = 0;
    for (size_t i = 0; i < size; ++i) {
        sum += arr[i];
    }
    return sum;
}


int raw_pointer_sum() {
    size_t size = 10000000;
    int* arr = new int[size];

    for (size_t i = 0; i < size; ++i) {
        arr[i] = i;
    }

    int sum = sum_elements_raw(arr, size);
    delete[] arr;

    std::cout << "Sum: " << sum << std::endl;
    return 0;
}

int smart_pointer_sum() {
    size_t size = 10000000;
    std::unique_ptr<int[]> arr(new int[size]);

    for (size_t i = 0; i < size; ++i) {
        arr[i] = i;
    }

    int sum = sum_elements_smart(std::move(arr), size);

    std::cout << "Sum: " << sum << std::endl;
    return 0;
}

int main(void){

    raw_pointer_sum();
    smart_pointer_sum();

}