#include <algorithm>
#include <iostream>
#include <vector>
#include <random>
#include <chrono>

int partition_own(std::vector<int>& vec, int left, int right, int& comparison_count) {
    int pivot = vec[right];
    int i = left - 1;

    for (int j = left; j <= right - 1; ++j) {
        ++comparison_count;
        if (vec[j] < pivot) {
            ++i;
            std::swap(vec[i], vec[j]);
        }
    }
    std::swap(vec[i + 1], vec[right]);
    return i + 1;
}

void quick_sort_with_count(std::vector<int>& vec, int left, int right, int& comparison_count) {
    if (left < right) {
        int pivot_index = partition_own(vec, left, right, comparison_count);
        quick_sort_with_count(vec, left, pivot_index - 1, comparison_count);
        quick_sort_with_count(vec, pivot_index + 1, right, comparison_count);
    }
}

void insertion_sort_with_count(std::vector<int>& vec, int left, int right, int& comparison_count) {
    for (int i = left + 1; i <= right; ++i) {
        int key = vec[i];
        int j = i - 1;

        while (j >= left && vec[j] > key) {
            ++comparison_count;
            vec[j + 1] = vec[j];
            --j;
        }
        // Increment comparison_count for the last failed comparison
        if (j >= left) {
            ++comparison_count;
        }

        vec[j + 1] = key;
    }
}

void max_heapify(std::vector<int>& vec, int n, int i, int& comparison_count) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && vec[left] > vec[largest]) {
        largest = left;
        ++comparison_count;
    }

    if (right < n && vec[right] > vec[largest]) {
        largest = right;
        ++comparison_count;
    }

    if (largest != i) {
        std::swap(vec[i], vec[largest]);
        max_heapify(vec, n, largest, comparison_count);
    }
}

void heap_sort_with_count(std::vector<int>& vec, int& comparison_count) {
    int n = vec.size();

    // Build max heap
    for (int i = n / 2 - 1; i >= 0; --i) {
        max_heapify(vec, n, i, comparison_count);
    }

    // Extract elements from heap
    for (int i = n - 1; i > 0; --i) {
        std::swap(vec[0], vec[i]);
        max_heapify(vec, i, 0, comparison_count);
    }
}

void introsort_with_count(std::vector<int>& vec, int left, int right, int maxdepth, int& comparison_count) {
    int size = right - left + 1;
    if (size <= 16) {
        insertion_sort_with_count(vec, left, right, comparison_count);
    } else if (maxdepth == 0) {
        heap_sort_with_count(vec, comparison_count);
    } else {
        int pivot_index = partition_own(vec, left, right, comparison_count);
        introsort_with_count(vec, left, pivot_index - 1, maxdepth - 1, comparison_count);
        introsort_with_count(vec, pivot_index + 1, right, maxdepth - 1, comparison_count);
    }
}

int sort_and_count_comparisons_introsort(const std::vector<int>& vec) {
    std::vector<int> sorted_vec(vec);
    int comparison_count = 0;
    int maxdepth = 2 * floor(log2(sorted_vec.size()));
    introsort_with_count(sorted_vec, 0, sorted_vec.size() - 1, maxdepth, comparison_count);
    return comparison_count;
}

int sort_and_count_comparisons_quick_sort(const std::vector<int>& vec) {
    std::vector<int> sorted_vec(vec);
    int comparison_count = 0;
    quick_sort_with_count(sorted_vec, 0, sorted_vec.size() - 1, comparison_count);
    return comparison_count;
}

int sort_and_count_comparisons(const std::vector<int>& vec) {
    std::vector<int> sorted_vec(vec);
    int comparison_count = 0;
    std::sort(sorted_vec.begin(), sorted_vec.end(), [&comparison_count](int a, int b) {
        ++comparison_count;
        return a < b;
    });
    return comparison_count;
}

std::vector<int> generate_random_vector(int size) {
    std::vector<int> vec(size);
    std::iota(vec.begin(), vec.end(), 0);
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(vec.begin(), vec.end(), std::default_random_engine(seed));
    return vec;
}

int main() {
    int n = 1000;

    // Test cases
    std::vector<int> sorted_vec(n);
    std::iota(sorted_vec.begin(), sorted_vec.end(), 0);

    std::vector<int> reversed_vec(sorted_vec.rbegin(), sorted_vec.rend());

    std::vector<int> random_vec = generate_random_vector(n);

    std::vector<int> duplicate_elements_vec(n, 42);

    // Measure comparisons
    int sorted_comparisons = sort_and_count_comparisons(sorted_vec);
    int reversed_comparisons = sort_and_count_comparisons(reversed_vec);
    int random_comparisons = sort_and_count_comparisons(random_vec);
    int duplicate_elements_comparisons = sort_and_count_comparisons(duplicate_elements_vec);

    std::cout << "Comparisons for sorted input: " << sorted_comparisons << std::endl;
    std::cout << "Comparisons for reversed input: " << reversed_comparisons << std::endl;
    std::cout << "Comparisons for random input: " << random_comparisons << std::endl;
    std::cout << "Comparisons for duplicate elements input: " << duplicate_elements_comparisons << std::endl;

    int sorted_comparisons_quick_sort = sort_and_count_comparisons_quick_sort(sorted_vec);
    int reversed_comparisons_quick_sort = sort_and_count_comparisons_quick_sort(reversed_vec);
    int random_comparisons_quick_sort = sort_and_count_comparisons_quick_sort(random_vec);
    int duplicate_elements_comparisons_quick_sort = sort_and_count_comparisons_quick_sort(duplicate_elements_vec);

    std::cout << "Comparisons for QuickSort on sorted input: " << sorted_comparisons_quick_sort << std::endl;
    std::cout << "Comparisons for QuickSort on reversed input: " << reversed_comparisons_quick_sort << std::endl;
    std::cout << "Comparisons for QuickSort on random input: " << random_comparisons_quick_sort << std::endl;
    std::cout << "Comparisons for QuickSort on duplicate elements input: " << duplicate_elements_comparisons_quick_sort << std::endl;

    int sorted_comparisons_introsort = sort_and_count_comparisons_introsort(sorted_vec);
    int reversed_comparisons_introsort = sort_and_count_comparisons_introsort(reversed_vec);
    int random_comparisons_introsort = sort_and_count_comparisons_introsort(random_vec);
    int duplicate_elements_comparisons_introsort = sort_and_count_comparisons_introsort(duplicate_elements_vec);

    std::cout << "Comparisons for Introsort on sorted input: " << sorted_comparisons_introsort << std::endl;
    std::cout << "Comparisons for Introsort on reversed input: " << reversed_comparisons_introsort << std::endl;
    std::cout << "Comparisons for Introsort on random input: " << random_comparisons_introsort << std::endl;
    std::cout << "Comparisons for Introsort on duplicate elements input: " << duplicate_elements_comparisons_introsort << std::endl;

    return 0;
}