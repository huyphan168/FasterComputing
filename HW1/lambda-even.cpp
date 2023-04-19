#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

std::vector<int> filter_even_by_value(std::vector<int> vec) {
    std::vector<int> output_vector;
    auto is_even = [](int num) { return num % 2 == 0; };
    std::copy_if(vec.begin(), vec.end(), std::back_inserter(output_vector), is_even);
    return output_vector;
}

std::vector<int> filter_even_by_reference(const std::vector<int>& vec) {
    std::vector<int> output_vector;
    auto is_even = [](int num) { return num % 2 == 0; };
    std::copy_if(vec.begin(), vec.end(), std::back_inserter(output_vector), is_even);
    return output_vector;
}

int main() {
    std::vector<int> input_vector = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    std::vector<int> output_vector_by_value = filter_even_by_value(input_vector);
    std::vector<int> output_vector_by_reference = filter_even_by_reference(input_vector);

    std::cout << "By value: ";
    for (int num : output_vector_by_value) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::cout << "By reference: ";
    for (int num : output_vector_by_reference) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
