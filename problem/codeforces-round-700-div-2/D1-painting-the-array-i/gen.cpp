#include <iostream>
#include <random>
std::random_device rd;
std::mt19937 e(rd());
std::uniform_int_distribution<int> d(1, 5);

int main() {
  for (int i = 0; i < 12; ++i) {
    std::cout << d(e) << ' ';
  }
  return 0;
}