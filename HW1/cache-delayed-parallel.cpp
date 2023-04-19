#include <iostream>
#include <chrono>
#include <thread>

const double M = 8e8;

struct Input {
  long int n1 = 1;
  char padding[64]; // Add padding to separate n1 and n2
  long int n2 = 1;
};

void part1(Input& input) {
  for (; input.n1 < M; input.n1 += input.n1 % 3);
}

void part2(Input& input) {
  for (; input.n2 < M; input.n2 += input.n2 % 3);
}

void parallel() {
  Input input;
  std::thread t1(part1, std::ref(input));
  std::thread t2(part2, std::ref(input));
  t1.join();
  t2.join();
}

void sequential() {
  Input input;
  part1(input);
  part2(input);
}

int main() {
  auto start = std::chrono::high_resolution_clock::now();
  parallel();
  auto end = std::chrono::high_resolution_clock::now();
  std::cout << "Parallel time: " << std::chrono::duration<double>(end - start).count() << " s\n";

  start = std::chrono::high_resolution_clock::now();
  sequential();
  end = std::chrono::high_resolution_clock::now();
  std::cout << "Sequential time: " << std::chrono::duration<double>(end - start).count() << " s\n";

  return 0;
}