#include <cstdio>
#include <iostream>
#include <random>
const int N = 100000;
int a[N];

int c1 = 100, c2 = 100;

int main() {
  srand(time(0));
  puts("100000 1000000 10000004");
  for (int i = N - 1; i > 0; --i) {
     if (rand() % 500 == 0 && c1) a[i] = 1, --c1;
  }
  for (int i = N - 1; i > 0; --i) {
    if (rand() % 500 == 0 && c2) a[i] = -1, --c2;
  }
  for (int i = 0; i < N; ++i) {
    printf("%d ", a[i]);
  }
  return 0;
}
